#include <Wire.h>
#define SLAVE 4       // 슬레이브 주소

void setup() {
  Wire.begin();         // 마스터 모드로 Wire 라이브러리 초기화
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(SLAVE, 2);     // 슬레이브에 2 바이트 크기의 데이터 요청
  int count = read_2_byte_from_I2C(); // 슬레이브로부터 2바이트 데이터 수신
  Serial.println(String("슬레이브 카운터 : ") + count);

  delay(1000);
}

int read_2_byte_from_I2C() {
  byte buffer[2];       // 데이터 수신 버퍼

  for (int receiveCount = 0; receiveCount < 2; ) {
    if (Wire.available()) {     // 데이터 수신 확인
      buffer[receiveCount] = Wire.read(); // 데이터 읽기
      receiveCount++;
    }
  }

  return (buffer[0] << 8) | buffer[1];  // 2바이트 데이터로 int 타입 값 조합
}
