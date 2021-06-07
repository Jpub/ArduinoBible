#include <SoftwareSerial.h>

SoftwareSerial SSerial(2, 3);    // (RX, TX)

void setup() {
  Serial.begin(9600);     // 컴퓨터와의 연결
  SSerial.begin(9600);      // 슬레이브와의 연결
}

void loop() {
  if (SSerial.available()) {    // 데이터 수신 확인
    byte data = SSerial.read();   // 데이터 읽기

    Serial.println(String("슬레이브로부터 수신한 값 : ") + (int)data);
  }
}
