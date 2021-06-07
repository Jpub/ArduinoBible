#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(2, 3);     // 소프트웨어 시리얼 포트 (RX, TX)
boolean NewLine = true;

void setup() {
  Serial.begin(115200);       // 컴퓨터와의 시리얼 통신 초기화
  ESPSerial.begin(115200);    // ESP-01 모듈과의 시리얼 통신 초기화
}

void loop() {
  if (Serial.available()) {     // 시리얼 모니터 → 아두이노 → ESP-01 모듈
    char ch = Serial.read();

    ESPSerial.write(ch);
    if (NewLine) {
      Serial.print("\n> ");
      NewLine = false;
    }
    if (ch == '\n') {
      NewLine = true;
    }
    Serial.write(ch);
  }

  if (ESPSerial.available()) {  // ESP-01 모듈 → 아두이노 → 시리얼 모니터
    char ch = ESPSerial.read();
    Serial.write(ch);
  }
}
