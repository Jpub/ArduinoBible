#include <WiFiEsp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(2, 3);     // ESP-01 모듈 연결 포트

char AP[] = "your AP";
char PW[] = "your password";

char HOST[] = "www.openweathermap.org";

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
}

void loop() {
  String host = "www.deu.ac.kr";

  Serial.println();
  Serial.println("* " + host + "로 PING 시작...");

  int time = myPing(host, 5);
  
  Serial.println(String(" => PING 반환 시간 : ") + time + " ms");
  Serial.println("* PING 끝...");

  delay(5000);
}

int myPing(String host, int second) {
  String pingCommand = "AT+PING=\"" + host + '\"';
  ESPSerial.println(pingCommand);   // AT 명령 실행

  String buffer = "";
  unsigned long time = millis();
  boolean endOfResponse = false;
  int responseTime = -1;

  while (1) {
    if ((time + second * 1000) < millis()) {
      Serial.println(" => 시간 초과...");
      break;
    }
    if (endOfResponse) {
      break;
    }

    if (ESPSerial.available()) {
      char ch = ESPSerial.read();

      buffer += ch;

      if (buffer.startsWith("OK") || buffer.startsWith("ERROR")) {
        endOfResponse = true;
        Serial.println(" => 응답의 끝 발견...");
      }

      if (ch == '\n') {
        if (buffer.startsWith("+timeout")) {
          responseTime = -1;
        }
        else if (buffer[0] == '+') {
          responseTime = buffer.substring(1).toInt();
        }
        buffer = "";
      }
    }
  }

  return responseTime;
}
