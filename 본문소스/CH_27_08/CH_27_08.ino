#include <SoftwareSerial.h>

byte TERMINATOR = 0;
int count = 999;       // 카운터

SoftwareSerial SSerial(2, 3);     // (RX, TX)

void setup() {
  SSerial.begin(9600);      // 마스터와의 연결
}

void loop() {
  count = count + 1;      // 카운터 증가

  char buffer[6];
  sprintf(buffer, "%05d", count);   // 5자리 고정 길이 문자열로 변환

  byte checksum = 0;
  for (int i = 0; i < 5; i++) {   // 오류 검출을 위한 체크섬 계산
    checksum = checksum ^ buffer[i];
  }

  for (int i = 0; i < 5; i++) {   // 고정 길이 문자열 전송
    SSerial.write(buffer[i]);
  }
  SSerial.write(checksum);    // 체크섬 전송
  SSerial.write(TERMINATOR);    // 문자열의 끝 표시 전송

  delay(1000);        // 1초 대기
}
