#include <SoftwareSerial.h>

SoftwareSerial SSerial(2, 3);    // (RX, TX)

byte count = 0;       // 카운터

void setup() {
  SSerial.begin(9600);      // 마스터와의 연결
}

void loop() {
  count = count + 1;      // 카운터 증가
  SSerial.write(count);     // 카운터 값 전송

  delay(1000);        // 1초 대기
}
