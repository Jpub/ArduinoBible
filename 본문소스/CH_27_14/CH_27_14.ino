#include <Wire.h>
#define SLAVE1 4       // 슬레이브1 주소
#define SLAVE2 5      // 슬레이브2 주소

byte count = 0;         // 마스터 카운터

void setup() {
  Wire.begin();         // 마스터 모드로 Wire 라이브러리 초기화
}

void loop() {
  count++;

  if (count % 2) {
    Wire.beginTransmission(SLAVE1);   // I2C 통신을 통한 전송 시작
    Wire.print(count);      // * print 함수 사용
    Wire.print('\n');
    Wire.endTransmission(SLAVE1);   // I2C 통신을 통한 전송 끝
  }
  else {
    Wire.beginTransmission(SLAVE2);   // I2C 통신을 통한 전송 시작
    char buffer[4];
    sprintf(buffer, "%d", count);   // 숫자를 문자열로 변환
    for (int i = 0; i < strlen(buffer); i++) {
      Wire.write(buffer[i]);    // * write 함수 사용
    }
    Wire.write('\n');
    Wire.endTransmission(SLAVE2);   // I2C 통신을 통한 전송 끝
  }

  delay(1000);
}
