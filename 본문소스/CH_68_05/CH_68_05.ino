#include <WiFiEsp.h>
#include <SoftwareSerial.h>

#define PRINTOUT_JSON_DATA     // 날씨 정보 JSON 데이터 출력 여부

#define QUERY_INTERVAL 20000L   // 20초 간격으로 날씨 정보 요청
#define SERVER_TIMEOUT 10000L   // 서버 응답 대기 시간 10초

#define STATE_IDLE    0 // 날씨 정보 요청 대기 상태
#define STATE_RECEIVING_INFO  1 // 날씨 정보 요청 후 정보 수신 상태

#define HEADER_LENGTH_MAX 100   // 서버가 보내는 헤더 한 줄의 최대 길이
#define JSON_LENGTH_MAX 500     // JSON 형식 날씨 데이터 최대 길이

SoftwareSerial ESPSerial(2, 3);     // ESP-01 모듈 연결 포트

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";
String KEY = "your_OpenWeather_API_key_here";

char HOST[] = "api.openweathermap.org";

String requestStr1
  = "GET /data/2.5/weather?id=1838524&APPID=" + KEY + " HTTP/1.1";
String requestStr2 = String("Host: ") + HOST;
String requestStr3 = "Connection: close";

int state = STATE_IDLE;       // 날씨 정보 요청 대기 상태로 시작
int process_state = 0;      // 수신 정보 처리 단계
unsigned long time_previous, time_current;

char buffer[JSON_LENGTH_MAX + 1];
int buffer_idx = 0;     // 버퍼 내 데이터 저장 위치

String weatherString, tempString;   // 수신한 날씨 및 기온 정보

WiFiEspClient client;       // 웹 클라이언트
int brace_count;      // JSON 정보 끝 판별을 위한 중괄호 개수

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 UART 시리얼 연결
  ESPSerial.begin(9600);      // ESP-01 모듈과의 UART 시리얼 연결

  // 'AT'에 대한 응답 확인, 리셋, 스테이션 모드 설정, SDK 버전 호환 확인
  WiFi.init(&ESPSerial);      // ESP-01 모듈 초기화

  // AP 접속
  Serial.println(String("* \'") + AP + F("\'에 연결을 시도합니다."));
  if (WiFi.begin(AP, PW) != WL_CONNECTED) {
    Serial.println(F("** AP에 연결할 수 없습니다."));
    while (1);
  }
  else {
    Serial.println(F("* AP에 연결되었습니다."));
  }
  Serial.println();

  time_current = millis();
  time_previous = time_current - QUERY_INTERVAL;
}

void cleanUpTCPconnection() {     // TCP 연결 끊기
  if (client.connected()) {     // 연결된 경우
    client.flush();       // 수신 버퍼 비우기
    client.stop();      // 연결 끊기
  }
}

void loop() {
  time_current = millis();

  // 이전 날씨 정보 요청 이후 일정 시간이 경과한 경우 다시 정보 요청
  if (state == STATE_IDLE) {
    if (time_current - time_previous > QUERY_INTERVAL) {
      requestWeatherInformation();  // 날씨 정보 요청
    }
  }
  // 서버로부터 정보 수신 대기
  else if (state == STATE_RECEIVING_INFO) {
    // 서버로부터 데이터 수신이 지연된 경우
    if (time_current - time_previous > SERVER_TIMEOUT) {
      Serial.println(F("** 날씨 정보 수신 과정에 오류가 발생했습니다."));

      time_previous = millis();
      state = STATE_IDLE;
      cleanUpTCPconnection();     // TCP 연결 끊기
    }
    else {
      processReceivedInformation();   // 데이터 수신 및 처리
    }
  }
}

void requestWeatherInformation() {
  state = STATE_RECEIVING_INFO;

  if (!client.connect(HOST, 80)) {    // TCP 연결 오류
    Serial.println(F("** 날씨 서버 접속 과정에 오류가 발생했습니다."));

    time_previous = millis();
    state = STATE_IDLE;
    cleanUpTCPconnection();     // TCP 연결 끊기
  }
  else { // GET 메시지 전송
    Serial.println(F("** 날씨 서버에 날씨 정보를 요청합니다."));
    client.println(requestStr1);
    client.println(requestStr2);
    client.println(requestStr3);
    client.println();

    // GET 메시지 전송 후 서버로부터 정보 수신 모드로 전환
    time_previous = millis();
    buffer_idx = 0;       // 수신 버퍼 저장 위치
    process_state = 0;      // 수신 정보 처리 시작
    Serial.println(F("** 날씨 정보를 요청하고 응답을 기다립니다."));
  }
}

void processReceivedInformation() {
  while (client.available()) {
    char data = client.read();

    if (process_state == 0) {     // 헤더 수신 시작을 기다리는 상태
      buffer[buffer_idx] = data;
      buffer_idx = (buffer_idx + 1) % HEADER_LENGTH_MAX;

      if (buffer_idx >= 2 && data == '\n') {
        buffer[buffer_idx] = 0;
        if (strstr(buffer, "HTTP/1.1 200 OK")) {  // ‘HTTP/1.1 200 OK’ 문장 수신
          process_state = 1;    // 헤더 수신 종료를 기다리는 상태로 전환
        }
        buffer_idx = 0;
      }
    }
    else if (process_state == 1) {    // 헤더 수신 종료를 기다리는 상태
      buffer[buffer_idx] = data;
      buffer_idx = (buffer_idx + 1) % HEADER_LENGTH_MAX;

      if (buffer_idx > 2 && data == '\n') {
        buffer_idx = 0;
      }
      // “\r\n”으로만 이루어진 문장은 헤더 끝을 나타냄
      if (buffer_idx == 2 && data == '\n') {
        process_state = 2;  // JSON 데이터 수신 종료를 기다리는 상태로 전환
        buffer_idx = 0;
        brace_count = 0;    // JSON 데이터 종료 검사
      }
    }
    else if (process_state == 2) {    // JSON 데이터 수신 종료를 기다리는 상태
      buffer[buffer_idx] = data;
      buffer_idx = (buffer_idx + 1) % JSON_LENGTH_MAX;

      if (data == '{') {      // 여는 괄호
        brace_count++;
      }
      else if (data == '}') {   // 닫는 괄호
        brace_count--;
      }

      if (brace_count == 0) {   // 괄호가 모두 쌍을 이룬 경우
        buffer[buffer_idx] = 0;
        Serial.println(F("** 날씨 정보를 성공적으로 수신했습니다."));

#ifdef PRINTOUT_JSON_DATA   // JSON 데이터 출력
        Serial.println();
        Serial.print(F(" * 수신한 데이터 크기 : "));
        Serial.print(strlen(buffer));
        Serial.print(F("바이트\n * "));
        Serial.println(buffer);
#endif
        extractWeatherInformation();  // JSON 데이터에서 날씨와 기온 추출

        time_previous = millis();
        state = STATE_IDLE;

        cleanUpTCPconnection();   // TCP 연결 끊기
      }
    }
  }
}

void extractWeatherInformation() {
  char *key1 = "\"description\"", *key2 = "\"temp\"", *found;
  int index;

  found = strstr(buffer, key1) + strlen(key1) + 2;
  Serial.print(F("\n => 날씨 : "));
  weatherString = "";
  for (index = 0; index < 30; index++) {  // 날씨 데이터 최대 길이 30
    if (*found == '\"') {
      break;
    }
    weatherString += *found;
    found++;
  }
  Serial.println(weatherString);

  found = strstr(buffer, key2) + strlen(key2) + 1;
  Serial.print(F(" => 기온 : "));
  tempString = "";
  for (index = 0; index < 10; index++) {  // 기온 데이터 최대 길이 10
    if (*found == ',') {
      break;
    }
    tempString += *found;
    found++;
  }
  Serial.print(tempString + " K (");
  Serial.print(tempString.toFloat() - 273.15, 2); // 켈빈 온도를 섭씨 온도로 변환
  Serial.println(F(" C)\n"));
}
