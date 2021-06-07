#include <Wire.h>

void setup() {
  Wire.begin();       // I2C 통신 초기화
  Serial.begin(9600);     // UART 통신 초기화
}

void loop() {
  byte error, address;
  int nDevices = 0;     // 발견된 I2C 통신 장치 수

  Serial.println("* I2C 장치 스캔을 시작합니다...");
  for (address = 1; address < 127; address++ ) {
    // Write.endTransmisstion 함수는 전송에 대한 오류 여부를 반환함
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {       // 오류 없음, 즉, 장치가 존재함
      Serial.print(" 주소 0x");
      if (address < 16) {
        Serial.print('0');
      }
      Serial.print(address, HEX);
      Serial.println("에서 I2C 장치가 발견되었습니다.");

      nDevices++;
    }
  }
  if (nDevices == 0) {
    Serial.println("* I2C 장치가 발견되지 않았습니다.\n");
  }
  else {
    Serial.println("* 주소 스캔이 끝났습니다.\n");
  }

  delay(5000);        // 다음 스캔까지 5초 대기
}
