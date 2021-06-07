#include <SoftwareSerial.h>

byte TERMINATOR = 0;
int count = 999;        // 카운터

SoftwareSerial SSerial(2, 3);   // (RX, TX)

void setup() {
  SSerial.begin(9600);      // 마스터와의 연결
}

void loop() {
  count  = count + 1;     // 카운터 증가

  SSerial.print(count);       // 숫자를 문자열로 변환해서 전송
  SSerial.write(TERMINATOR);    // 문자열의 끝 표시 전송

  delay(1000);        // 1초 대기
}
