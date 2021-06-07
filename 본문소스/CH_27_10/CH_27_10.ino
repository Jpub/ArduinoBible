#include <Wire.h>
#define SLAVE 4       // 슬레이브 주소
#define TERMINATOR
int count = 0;

void setup() {
  Wire.begin();         // 마스터 모드로 Wire 라이브러리 초기화
}

void loop() {
  String str = "마스터 카운터 : ";

  Wire.beginTransmission(SLAVE);  // I2C 통신을 통한 전송 시작

  Wire.print(str);
  Wire.println(count++);

  Wire.endTransmission(SLAVE);    // I2C 통신을 통한 전송 끝

  delay(1000);
}
