#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(2, 3);    // ESP-01 모듈 연결 포트

String AP = "your_AP_name_here";
String PW = "your_AP_password_here";

String APconnectStr = "AT+CWJAP=\"" + AP + "\",\"" + PW + "\"";

byte connectionID;      // 접속한 클라이언트 ID
char buffer[6];       // 클라이언트 요청 데이터 저장
int index = 0;        // 버퍼에 저장할 위치

void setup() {
  Serial.begin(9600);     // 컴퓨터와의 UART 시리얼 연결
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

  // 다중 접속 허용
  if (!sendATcommand("AT+CIPMUX=1", "OK", 1)) {
    Serial.println(F("** 다중 접속 허용 과정에서 오류가 발생했습니다."));
    while (1);
  }
  else {
    Serial.println(F("** 다중 접속을 허용했습니다."));
  }

  // TCP 서버 생성
  if (!sendATcommand("AT+CIPSERVER=1,80", "OK", 1)) {
    Serial.println(F("** TCP 서버 생성 과정에서 오류가 발생했습니다."));
    while (1);
  }
  else {
    Serial.println(F("** TCP 서버를 생성했습니다."));
  }

  // 접속할 서버 주소 확인을 위해 IP 정보 출력
  printResponse("AT+CIFSR", 1);
  Serial.println();
}

// 지정한 시간 내에 지정한 응답 수신 여부로 AT 명령 실행 성공 여부 판단
boolean sendATcommand(String command, char *response, int second) {
  // 최대 대기 시간 설정
  ESPSerial.setTimeout(second * 1000);
  // AT 명령을 ESP-01 모듈로 전달하여 실행
  ESPSerial.println(command);
  // 응답 대기
  boolean responseFound = ESPSerial.find(response);
  // 최대 대기 시간을 디폴트값인 1초로 변경
  ESPSerial.setTimeout(1000);

  return responseFound;     // AT 명령 실행 성공 여부 반환
}

// AT 명령을 실행하고 지정한 시간 동안 응답 메시지를 시리얼 모니터로 출력
void printResponse(String command, int second) {
  ESPSerial.println(command);   // AT 명령 실행
  unsigned long time = millis();
  // 지정한 시간 동안 응답 메시지를 시리얼 모니터로 출력
  while ((time + second * 1000) > millis()) { // 응답 메시지 출력
    while (ESPSerial.available()) {
      Serial.print((char)ESPSerial.read());
    }
  }
}

// ‘AT+CIPSEND’ 명령 실행
void sendCIPSEND(String message) {
  // AT+CIPSEND=<link ID>,<length>
  String command = "AT+CIPSEND=";
  command += connectionID;
  command += ",";
  command += message.length();

  sendATcommand(command, "OK", 1);  // 'AT+CIPSEND' 명령 실행
  sendATcommand(message, "OK", 1);  // 프롬프트가 바뀐 후 전송 내용 입력
}

float readTemperature() {
  int reading = analogRead(A0);

  float voltage = reading * 5.0 / 1023.0;   // 전압으로 변환
  float temperature = voltage * 100;    // '전압 * 100'으로 온도 계산

  return temperature;
}

void sendResponse() {
  Serial.print(F("* 클라이언트 "));
  Serial.print(connectionID);
  Serial.println(F("번으로 온도 정보를 보냅니다."));

  String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n";
  header += "Connection:close\r\n\r\n";
  String temperature = String(readTemperature(), 2);
  String data = "<!DOCTYPE HTML>\r\n<html>\r\nTemperature : ";
  data += temperature + " C\r\n</html>\r\n\r\n";

  // 온도 정보를 나타내는 페이지를 헤더와 데이터 부분으로 나누어 전송
  sendCIPSEND(header);
  sendCIPSEND(data);

  // AT+CIPCLOSE=<link ID> : TCP 연결 종료
  String closeCommand = "AT+CIPCLOSE=";
  closeCommand += connectionID;
  closeCommand += "\r\n";

  boolean success = sendATcommand(closeCommand, "OK", 3);
  Serial.print(F("* 클라이언트 "));
  Serial.print(connectionID);
  Serial.print(F("번과의 접속"));

  if (success) {
    Serial.println(F("을 종료하였습니다.\n"));
  }
  else {
    Serial.println(F(" 종료에 문제가 있습니다. 확인이 필요합니다.\n"));
  }
}

void loop() {
  if (ESPSerial.available()) {
    char ch = ESPSerial.read();
    if (index < 6) {
      buffer[index] = ch;
    }
    index++;

    if (ch == '\n') {       // 문장의 끝
      if (startWith(buffer, "+IPD")) {  // '+IPD,n'로 시작하는 경우
        connectionID = buffer[5] - '0'; // '+IPD,n'에서 클라이언트 아이디 n 확인
        sendResponse();     // HTTP 응답 전송
      }
      index = 0;      // '+IPD'로 시작하지 않으면 처리하지 않음
    }
  }
}

boolean startWith(char *str, char *start) {
  for (byte i = 0; i < strlen(start); i++) {
    if (start[i] != str[i]) {
      return false;
    }
  }
  return true;
}
