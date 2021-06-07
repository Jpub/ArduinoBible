#include <Wire.h>

int ADDRESS = 0x68;       // MPU6050 칩의 I2C 주소
// 가속도, 온도, 각속도 저장을 위한 변수
int accX, accY, accZ, tmp, gyroX, gyroY, gyroZ;

void setup() {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);  // MPU6050 선택
  Wire.write(0x6B);       // PWR_MGMT_1 레지스터 선택
  Wire.write(0);        // 슬립 모드 해제
  Wire.endTransmission();
  Serial.begin(115200);       // 시리얼 통신 초기화
}

void loop() {
  Wire.beginTransmission(ADDRESS);  // MPU6050 선택
  Wire.write(0x3B);       // X축 방향 가속도 레지스터 선택
  // 연결을 종료하지 않으므로 beginTransmission 없이 읽기 가능
  Wire.endTransmission(false);
  Wire.requestFrom(ADDRESS, 14);  // 14바이트 데이터 요청

  accX = Wire.read() << 8 | Wire.read();  // ACCEL_XOUT
  accY = Wire.read() << 8 | Wire.read();  // ACCEL_YOUT
  accZ = Wire.read() << 8 | Wire.read();  // ACCEL_ZOUT
  tmp = Wire.read() << 8 | Wire.read();   // TEMP_OUT
  gyroX = Wire.read() << 8 | Wire.read();   // GYRO_XOUT
  gyroY = Wire.read() << 8 | Wire.read();   // GYRO_YOUT
  gyroZ = Wire.read() << 8 | Wire.read();   // GYRO_ZOUT
  Wire.endTransmission();     // 데이터 읽기 종료

  Serial.print(accX); Serial.print(' ');  // 가속도 데이터 출력
  Serial.print(accY); Serial.print(' ');
  Serial.println(accZ);

  delay(50);
}
