#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);  // 소프트웨어 시리얼 포트 (RX, TX)
boolean NewLine = true;

void setup() {
  Serial.begin(9600);   // 컴퓨터와의 시리얼 통신 초기화
  BTSerial.begin(9600);   // 블루투스 모듈과의 시리얼 통신 초기화
}

void loop() {
  if (Serial.available()) {   // 시리얼 모니터 → 아두이노 → 블루투스 모듈
    char ch = Serial.read();

    if (ch != '\r' && ch != '\n') { // 개행문자는 블루투스 모듈로 전달하지 않음
      BTSerial.write(ch);
    }
    if (NewLine) {
      Serial.print("\n> ");
      NewLine = false;
    }
    if (ch == '\n') {
      NewLine = true;
    }
    Serial.write(ch);
  }

  if (BTSerial.available()) { // 블루투스 모듈 → 아두이노 → 시리얼 모니터
    char ch = BTSerial.read();
    Serial.write(ch);
  }
}
