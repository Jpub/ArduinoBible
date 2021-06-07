#include <Wire.h>

int ADDRESS = 0x68;       // MPU6050 칩의 I2C 주소
int accX, accY, accZ;     // 가속도 저장 변수
double pitch, roll;     // 피치, 록

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
  Wire.requestFrom(ADDRESS, 6);   // 6바이트 데이터 요청

  accX = Wire.read() << 8 | Wire.read();  // ACCEL_XOUT
  accY = Wire.read() << 8 | Wire.read();  // ACCEL_YOUT
  accZ = Wire.read() << 8 | Wire.read();  // ACCEL_ZOUT
  Wire.endTransmission();     // 데이터 읽기 종료

  calcPitchRoll(accX, accY, accZ);  // 피치, 롤 계산

  Serial.print(pitch); Serial.print(' ');
  Serial.println(roll);

  delay(50);
}

void calcPitchRoll(int accX, int accY, int accZ) {
  double X = accX, Y = accY, Z = accZ;

  pitch = atan2(X, sqrt(Y * Y + Z * Z));  // 피치
  roll = atan2(Y, sqrt(X * X + Z * Z)); // 롤

  pitch = pitch * (180.0 / PI);   // 라디안(radian)을 디그리(degree)로 변환
  roll = roll * (180.0 / PI);
}
