#include <SoftwareSerial.h>

typedef union {        // 공용체 정의
  int no;
  byte b[2];
} INT;
INT count;

SoftwareSerial SSerial(2, 3);     // (RX, TX)
boolean start = false;      // 첫 번째 바이트 수신 여부

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 연결
  SSerial.begin(9600);      // 슬레이브와의 연결
}

void loop() {
  if (SSerial.available()) {    // 데이터 수신 확인
    byte data = SSerial.read();     // 데이터 읽기

    if (start == false) {       // 첫 번째 바이트를 받은 경우
      start = true;
      count.b[0] = data;
    }
    else {          // 두 번째 바이트를 받은 경우
      start = false;
      count.b[1] = data;
      Serial.println(String("슬레이브로부터 수신한 값 : ") + count.no);
    }
  }
}
