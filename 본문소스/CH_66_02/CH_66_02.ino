#include <SoftwareSerial.h>

#define PRINTOUT_JSON_DATA    // 날씨 정보 JSON 데이터 출력 여부

#define QUERY_INTERVAL 20000L   // 20초 간격으로 날씨 정보 요청
#define SERVER_TIMEOUT 10000L   // 서버 응답 대기 시간 10초

#define STATE_IDLE    0 // 날씨 정보 요청 대기 상태
#define STATE_RECEIVING_INFO  1 // 날씨 정보 요청 후 정보 수신 상태

#define HEADER_LENGTH_MAX   100   // 서버가 보내는 헤더 한 줄의 최대 길이
#define JSON_LENGTH_MAX   500   // JSON 형식 날씨 정보 최대 길이

SoftwareSerial ESPSerial(2, 3);   // ESP-01 모듈 연결 포트

String AP = "your_AP_name_here";
String PW = "your_AP_password_here";
String KEY = "your_OpenWeather_API_key_here";

String HOST = "api.openweathermap.org";

String APconnectStr = "AT+CWJAP=\"" + AP + "\",\"" + PW + "\"";
String serverConnectStr = "AT+CIPSTART=\"TCP\",\"" + HOST + "\",80";
String requestStr1
  = "GET /data/2.5/weather?id=1838524&APPID=" + KEY + " HTTP/1.1";
String requestStr2 = "Host: " + HOST;
String requestStr3 = "Connection: close";

int state = STATE_IDLE;       // 날씨 정보 요청 대기 상태로 시작
int process_state = 0;      // 수신 정보 처리 단계
unsigned long time_previous, time_current;

// ‘\r\n’까지 한 줄 단위로 처리하기 위한 버퍼, JSON 데이터 크기에 맞춰 할당
char buffer[JSON_LENGTH_MAX + 1];
int buffer_idx = 0;     // 버퍼 내 데이터 저장 위치

String weatherString, tempString;   // 수신한 날씨 및 기온 정보

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 UART 시리얼 연결
  ESPSerial.begin(9600);      // ESP-01 모듈과의 UART 시리얼 연결

  // ESP-01 모듈 리셋
  if (!sendATcommand("AT+RST", "ready", 3)) {
    Serial.println(F("** ESP-01 리셋 과정에서 오류가 발생했습니다."));
    while (1);
  }
  else {
    Serial.println(F("** ESP-01 모듈이 리셋되었습니다."));
  }

  // 소프트AP+스테이션 모드로 설정
  if (!sendATcommand("AT+CWMODE=3", "OK", 3)) {
    Serial.println(F("** ESP-01 모드 전환 과정에서 오류가 발생했습니다."));
    while (1);
  }
  else {
    Serial.println(F("** ESP-01을 모드 3으로 전환하였습니다."));
  }

  // AP 접속
  if (!sendATcommand(APconnectStr, "OK", 10)) {
    Serial.println(F("** AP 접속 과정에서 오류가 발생했습니다."));
    while (1);
  }
  else {
    Serial.println(F("** AP에 접속했습니다."));
  }

  time_current = millis();
  time_previous = time_current - QUERY_INTERVAL;
}

boolean sendATcommand(String command, char *response, int second) {
  // 최대 대기 시간 설정
  ESPSerial.setTimeout(second * 1000);
  // AT 명령을 ESP-01 모듈로 전달하여 실행
  ESPSerial.println(command);
  // 응답 대기
  boolean responseFound = ESPSerial.find(response);
  // 최대 대기 시간을 디폴트값인 1초로 변경
  ESPSerial.setTimeout(1000);

  return responseFound; // AT 명령 실행 성공 여부 반환
}

void loop() {
  time_current = millis();

  // 이전 날씨 정보 요청 이후 일정 시간이 지났을 때 다시 날씨 정보 요청
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
    }
    else {
      processReceivedInformation();   // 데이터 수신 및 처리
    }
  }
}

void requestWeatherInformation() {
  state = STATE_RECEIVING_INFO;

  if (!sendATcommand(serverConnectStr, "OK", 10)) {   // TCP 연결 오류
    Serial.println(F("** 날씨 서버 접속 과정에 오류가 발생했습니다."));

    time_previous = millis();
    state = STATE_IDLE;
  }
  else { // GET 메시지 전송
    sendATcommand("AT+CIPSEND=133", "OK\r\n>", 10);
    Serial.println(F("** 날씨 서버에 날씨 정보를 요청합니다."));

    ESPSerial.println(requestStr1);
    ESPSerial.println(requestStr2);
    ESPSerial.println(requestStr3);

    if (!sendATcommand("", "SEND OK", 5)) {   // GET 메시지 전송 오류
      Serial.println(F("** 날씨 정보 요청 과정에 오류가 발생했습니다."));

      time_previous = millis();
      state = STATE_IDLE;
    }
    else {
      // GET 메시지를 정상적으로 전송하고 서버로부터 정보 수신 모드로 전환
      time_previous = millis();
      buffer_idx = 0;       // 수신 버퍼 저장 위치
      process_state = 0;    // 수신 정보 처리 시작
      Serial.println(F("** 날씨 정보를 요청하고 응답을 기다립니다."));
    }
  }
}

void processReceivedInformation() {
  while (ESPSerial.available()) {
    char data = ESPSerial.read();

    if (process_state == 0) {     // 헤더 수신 시작을 기다리는 상태
      buffer[buffer_idx] = data;
      buffer_idx = (buffer_idx + 1) % HEADER_LENGTH_MAX;

      if (buffer_idx >= 2 && data == '\n') {
        buffer[buffer_idx] = 0;
        if (strstr(buffer, "+IPD")) {   // "+IPD"로 시작하는 문장 수신
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
      // ‘\r\n’으로만 이루어진 문장은 헤더 끝을 나타냄
      if (buffer_idx == 2 && data == '\n') {
        process_state = 2;  // JSON 데이터 수신 종료를 기다리는 상태로 전환
        buffer_idx = 0;
      }
    }
    else if (process_state == 2) {    // JSON 데이터 수신 종료를 기다리는 상태
      buffer[buffer_idx] = data;
      buffer_idx = (buffer_idx + 1) % JSON_LENGTH_MAX;

      // JSON 데이터 수신 종료
      if (buffer[buffer_idx - 1] == '\n') {
        buffer[buffer_idx] = 0;
        Serial.println(F("** 날씨 정보를 성공적으로 수신했습니다."));

#ifdef PRINTOUT_JSON_DATA   // JSON 데이터 출력
        Serial.println();
        Serial.print(F(" * 수신한 데이터 크기 : "));
        Serial.print(strlen(buffer));
        Serial.print(F("바이트\n * "));
        Serial.print(buffer);
#endif
        extractWeatherInformation();  // JSON 데이터에서 날씨와 기온 추출

        time_previous = millis();
        state = STATE_IDLE;
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
  for (index = 0; index < 30; index++) {  // 날씨 정보 최대 길이 30
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
