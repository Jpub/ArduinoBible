#include <SoftwareSerial.h>

typedef union {        // 공용체 정의
  int no;
  byte b[2];
} INT;
INT count;          // 카운터

SoftwareSerial SSerial(2, 3);     // (RX, TX)

void setup() {
  SSerial.begin(9600);      // 마스터와의 연결
  count.no = 999;
}

void loop() {
  count.no = count.no + 1;    // 카운터 증가

  SSerial.write(count.b[0]);    // int 타입의 첫 번째 바이트 전송
  SSerial.write(count.b[1]);    // int 타입의 두 번째 바이트 전송

  delay(1000);        // 1초 대기
}
