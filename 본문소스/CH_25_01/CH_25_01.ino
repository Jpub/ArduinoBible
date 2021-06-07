#include <SoftwareSerial.h>

SoftwareSerial HM10(3, 2);     // (RX, TX) -> HM-10의 (TX, RX)

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 통신 초기화
  HM10.begin(115200);       // 블루투스 모듈과의 시리얼 통신 초기화
}

void loop() {
  if (Serial.available()) {     // 시리얼 모니터 → 아두이노 → 블루투스 모듈
    char ch = Serial.read();
    Serial.write(ch);
    HM10.write(ch);
  }

  if (HM10.available()) {     // 블루투스 모듈 → 아두이노 → 시리얼 모니터
    char ch = HM10.read();
    Serial.write(ch);
  }
}
