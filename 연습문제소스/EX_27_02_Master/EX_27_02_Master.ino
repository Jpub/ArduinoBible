#include <Wire.h>
#define SLAVE 4       // 슬레이브 주소

void setup() {
  Wire.begin();         // 마스터 모드로 Wire 라이브러리 초기화
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(SLAVE, 5);
  int vr;
  boolean receive_error = read_5_byte_from_I2C(&vr);
  Serial.print(String("가변저항 값 : ") + vr);
  if (receive_error) {
    Serial.println(" (데이터 오류)");
  }
  else {
    Serial.println(" (데이터 정상)");
  }

  delay(1000);
}

boolean read_5_byte_from_I2C(int *vr) {
  char buffer[5];

  for (int receiveCount = 0; receiveCount < 5; ) {
    if (Wire.available()) {
      buffer[receiveCount] = Wire.read();
      receiveCount++;
    }
  }

  byte checksum = 0;
  for (int i = 0; i < 4; i++) {
    checksum = checksum ^ buffer[i];
  }
  boolean receive_error = !(checksum == buffer[4]);

  buffer[4] = 0;
  *vr = String(buffer).toInt();

  return receive_error;
}
