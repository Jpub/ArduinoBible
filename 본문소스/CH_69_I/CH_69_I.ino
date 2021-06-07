#include <WiFiEsp.h>
#include <SoftwareSerial.h>

#define HEADER_LENGTH_MAX 100   // 서버가 보내는 헤더 한 줄의 최대 길이

SoftwareSerial ESPSerial(2, 3);     // ESP-01 모듈 연결 포트
WiFiEspServer server(80);

int pinLED = 11;        // LED 연결 핀
int ledState = LOW;     // LED 현재 상태
int requestState;       // 클라이언트의 요청 종류

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";

char buffer[HEADER_LENGTH_MAX + 1];   // 수신 버퍼
int index = 0;        // 버퍼 내 데이터 저장 위치

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 UART 시리얼 연결
  ESPSerial.begin(9600);      // ESP-01 모듈과의 UART 시리얼 연결

  WiFi.init(&ESPSerial);      // ESP-01 모듈 초기화
  Serial.println(String("* \'") + AP + "\'에 연결을 시도합니다.");
  int status = WiFi.begin(AP, PW);  // AP에 연결 시도

  if (status != WL_CONNECTED) {
    Serial.println(F("** AP에 연결할 수 없습니다."));
    while (1);
  }
  else {
    Serial.println(F("* AP에 연결되었습니다."));
  }
  Serial.println();

  server.begin();       // 서버 시작
  Serial.println(F("* 서버를 시작합니다."));

  IPAddress ip = WiFi.localIP();    // 서버 IP 주소 출력
  Serial.print(F(" => 서버 IP 주소\t: "));
  Serial.println(ip);
  Serial.println();

  pinMode(pinLED, OUTPUT);    // LED 연결 핀을 출력으로 설정
  digitalWrite(pinLED, ledState);   // 점멸 제어
}

void loop() {
  WiFiEspClient client = server.available();
  if (client) {         // 클라이언트 연결
    index = 0;        // 버퍼 초기화
    Serial.println(F("* 클라이언트 요청이 들어왔습니다."));

    while (client.connected()) {    // 클라이언트가 연결된 동안
      if (client.available()) {     // 데이터 수신
        char ch = client.read();
        buffer[index] = ch;
        index = (index + 1) % HEADER_LENGTH_MAX;
        buffer[index] = 0;    // 문자열 처리를 위한 끝 표시

        if (ch == '\n') {       // 문장의 끝
          if (index == 2) {     // 빈 문장, 즉, 헤더의 마지막 문장인 경우
            Serial.println(F("* LED 제어 결과를 전송합니다."));
            sendResponse(client, requestState);   // HTTP 응답 전송

            Serial.println(F("* 클라이언트와의 연결을 종료합니다."));
            Serial.println();
            client.stop();    // 클라이언트와의 연결 종료
          }
          else if (strstr(buffer, "GET")) { // 클라이언트 요청 파악
            requestState = processRequest();
          }
          else {
            index = 0;      // 다른 헤더 문장은 처리하지 않음
          }
        }
      }
    }
  }
}

int processRequest() {
  // 2개의 공백문자 사이에 있는 주소 추출
  String requestString = findRequestString();
  if (requestString.length() == 0) {    // 주소 추출 실패
    return –1;        // 오류
  }

  if (requestString.equals("/")) {    // 메인 페이지 요청
    return 1;
  }
  else if (requestString.equals("/on")) {   // LED 켜기 요청
    return (ledState + 1) * 10 + 2;
  }
  else if (requestString.equals("/off")) {  // LED 끄기 요청
    return (ledState + 1) * 10 + 1;
  }
  else {
    return -1;        // 알 수 없는 주소
  }
}

String findRequestString() {
  int N = strlen(buffer), p, pos1 = 0, pos2 = 0;
  String requestString = "";

  for (p = 0; p < N; p++) {     // 첫 번째 공백문자 위치
    if (buffer[p] == ' ') {
      pos1 = p;
      break;
    }
  }

  for (p = pos1 + 1; p < N; p++) {  // 두 번째 공백문자 위치
    if (buffer[p] == ' ') {
      pos2 = p;
      break;
    }
    requestString += buffer[p];
  }

  if (pos1 == 0 || pos2 == 0) {     // 두 개의 공백문자가 발견되지 않음
    requestString = "";
  }
  return requestString;
}

void sendStateControlMessage(WiFiEspClient client) {
  client.print(F("현재 LED 상태 : "));
  client.print(ledState ? F("ON<br><br>") : F("OFF<br><br>"));

  client.print(F("LED 켜기 : \'서버_주소/on\' 으로 접속하세요.<br>\r\n"));
  client.print(F("LED 끄기 : \'서버_주소/off\' 로 접속하세요.\r\n"));
}

void sendResponse(WiFiEspClient client, int requestState) {
  client.print("HTTP/1.1 200 OK\r\n");  // 헤더
  client.print("Content-Type: text/html; charset=utf-8\r\n");
  client.print("Connection:close\r\n");
  client.print("\r\n");

  client.print("<!DOCTYPE HTML>\r\n");  // 데이터 시작
  client.print("<html>\r\n");

  if (requestState == -1) {   // 오류 발생
    client.print(F("오류가 발생했습니다.<br><br>\r\n"));
    sendStateControlMessage(client);
    Serial.println(F(" => 오류가 발생했습니다."));
  }
  else if (requestState == 1) {   // 메인 페이지 요청
    sendStateControlMessage(client);
    Serial.println(F(" => 메인 페이지를 전송합니다."));
  }
  else if (requestState == 11) {    // LED OFF -> OFF
    client.print(F("OFF 상태가 유지되었습니다.<br><br>"));
    sendStateControlMessage(client);
    Serial.println(F(" => OFF 상태가 유지되었습니다."));
  }
  else if (requestState == 12) {    // LED OFF -> ON
    ledState = true;
    digitalWrite(pinLED, ledState);
    client.print(F("ON 상태로 바뀌었습니다.<br><br>"));
    sendStateControlMessage(client);
    Serial.println(F(" => ON 상태로 바뀌었습니다."));
  }
  else if (requestState == 21) {    // LED ON -> OFF
    ledState = false;
    digitalWrite(pinLED, ledState);
    client.print(F("OFF 상태로 바뀌었습니다.<br><br>"));
    sendStateControlMessage(client);
    Serial.println(F(" => OFF 상태로 바뀌었습니다."));
  }
  else if (requestState == 22) {    // LED ON -> ON
    client.print(F("ON 상태가 유지되었습니다.<br><br>"));
    sendStateControlMessage(client);
    Serial.println(F(" => ON 상태가 유지되었습니다."));
  }

  client.print("</html>\r\n");     // 데이터 끝
  client.print("\r\n");
}
