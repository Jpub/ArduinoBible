#include <WiFiEsp.h>
#include <AltSoftSerial.h>
#include "CircularStringFinder.h"

#define QUERY_INTERVAL 20000L   // 20초 간격으로 날씨 정보 요청
#define SERVER_TIMEOUT 10000L   // 서버 응답 대기 시간 10초

#define STATE_IDLE 0      // 날씨 정보 요청 대기 상태
#define STATE_RECEIVING_INFO 1  // 날씨 정보 요청 후 정보 수신 상태

#define HEADER_LENGTH_MAX 100   // 서버가 보내는 헤더 한 줄의 최대 길이
//#define JSON_LENGTH_MAX 500   // JSON 형식 날씨 데이터 최대 길이

AltSoftSerial ESPSerial;      // ESP-01 모듈 연결 포트

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";
String KEY = "your_OpenWeather_API_key_here";

char HOST[] = "api.openweathermap.org";

String requestStr1
  = "GET /data/2.5/weather?id=1838524&APPID=" + KEY + " HTTP/1.1";
String requestStr2 = String("Host: ") + HOST;
String requestStr3 = "Connection: close";

int state = STATE_IDLE;       // 날씨 정보 요청 대기 상태로 시작
unsigned long time_previous, time_current;

char key1[] = "description\":\"";     // 날씨 정보 시작 문자열
char key2[] = "temp\":";      // 기온 정보 시작 문자열

CircularStringFinder csf(20);   // 문자열 검색 객체 생성
int foundCount = 0;

boolean braceStart = false;   // 데이터 수신 종료 검사를 위한 괄호 맞춤
int braceCount = 0;

String weatherString, tempString;   // 수신한 날씨 및 기온 정보

WiFiEspClient client;       // 웹 클라이언트

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

void requestWeatherInformation() {
  state = STATE_RECEIVING_INFO;

  if (!client.connect(HOST, 80)) {    // TCP 연결 오류
    Serial.println(F("** 날씨 서버 접속 과정에 오류가 발생했습니다."));

    time_previous = millis();
    state = STATE_IDLE;
    cleanUpTCPconnection();     // TCP 연결 끊기
  }
  else {            // GET 메시지 전송
    Serial.println(F("** 날씨 서버에 날씨 정보를 요청합니다."));
    client.println(requestStr1);
    client.println(requestStr2);
    client.println(requestStr3);
    client.println();

    // GET 메시지 전송 후 서버로부터 정보 수신 모드로 전환
    time_previous = millis();
    Serial.println(F("** 날씨 정보를 요청하고 응답을 기다립니다."));
  }
}

void loop() {
  time_current = millis();

  // 이전 날씨 정보 요청 이후 일정 시간이 경과한 경우 다시 정보 요청
  if (state == STATE_IDLE) {
    if (time_current - time_previous > QUERY_INTERVAL) {
      requestWeatherInformation();  // 날씨 정보 요청

      weatherString = "";     // 첫 번째 시작 문자열에 해당하는 날씨 값
      tempString = "";      // 두 번째 시작 문자열에 해당하는 온도 값

      braceStart = false;     // 헤더 이후 데이터 수신 시작
      braceCount = 0;     // 데이터 수신 종료 판단

      csf.setKey(key1, '\"'); // 첫 번째 시작 문자열 탐색, 종료 문자는 큰따옴표
      foundCount = 0;
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

void processReceivedInformation() {
  while (client.available()) {
    char data = client.read();

    if (data == '{' || data == '[') {   // 여는 괄호
      braceCount++;
      braceStart = true;      // 첫 번째 여는 괄호가 데이터 시작
    }
    else if (data == '}' || data == ']') {  // 닫는 괄호
      braceCount--;
      if (braceStart && braceCount == 0) {    // 데이터 수신 종료
        Serial.println(F("** 날씨 정보를 성공적으로 수신했습니다."));
        Serial.print(F("\n => 날씨 : "));
        Serial.println(weatherString);

        Serial.print(F(" => 기온 : "));
        Serial.print(tempString + " K (");
        Serial.print(tempString.toFloat() - 273.15, 2);   // 섭씨 온도로 변환
        Serial.println(F(" C)\n"));

        time_previous = millis();
        state = STATE_IDLE;

        cleanUpTCPconnection();   // TCP 연결 끊기
      }
    }
    else if (foundCount < 2) {    // 2개 값 검색 완료 이후 검색 중지
      byte searchStatus = csf.add(data);

      if (searchStatus == STATE_VALUE_FOUND) {
        foundCount++;
        if (foundCount == 1) {    // 날씨 문자열 수신 완료
          weatherString = csf.getValue();
          csf.setKey(key2, ',');  // 두 번째 시작 문자열 탐색, 종료 문자는 콤마
        }
        else if (foundCount == 2) {   // 기온 문자열 수신 완료
          tempString = csf.getValue();
        }
      }
    }
  }
}
