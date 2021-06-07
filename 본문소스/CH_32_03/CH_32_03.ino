#include <Wire.h>

#define SENSITIVITY   131.0   // 각속도 측정 범위, 표 32.5 참고
#define WEIGHT  0.98

int ADDRESS = 0x68;       // MPU6050 칩의 I2C 주소
int accX, accY, accZ;       // 가속도 저장 변수
int gyroX, gyroY, gyroZ;    // 각속도 저장 변수
int tmp;              // 온도 저장 변수
unsigned long time_previous;

double accelPitch, accelRoll, gyroPitch, gyroRoll;  // 가속도, 각속도에 의한 피치, 롤
double pitch = 0, roll = 0;     // 피치, 록

void setup() {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);  // MPU6050 선택
  Wire.write(0x6B);       // PWR_MGMT_1 레지스터 선택
  Wire.write(0);        // 슬립 모드 해제
  Wire.endTransmission();
  Serial.begin(115200);

  time_previous = micros();
}

void loop() {
  readAccelGyroData();

  calcAccelPitchRoll();       // 가속도 기반 피치, 롤 계산
  calcGyroPitchRoll();      // 각속도 기반 피치, 롤 계산
  complementaryFilter();      // 상보 필터 적용

  Serial.print(pitch);
  Serial.print('\t');
  Serial.print(roll);
  Serial.println();

  delay(5);
}

void complementaryFilter() {    // 상보 필터 적용
  pitch = WEIGHT * (pitch + gyroPitch) + (1 - WEIGHT) * accelPitch;
  roll = WEIGHT * (roll + gyroRoll) + (1 - WEIGHT) * accelRoll;
}

void calcAccelPitchRoll() {   // 가속도를 사용한 피치, 롤
  double X = accX, Y = accY, Z = accZ;

  accelPitch = atan2(X, sqrt(Y * Y + Z * Z));   // 피치
  accelRoll = atan2(Y, sqrt(X * X + Z * Z));  // 롤

  accelPitch = accelPitch * (180.0 / PI);   // 디그리(degree)로 변환
  accelRoll = accelRoll * (180.0 / PI);
}

void calcGyroPitchRoll() {      // 각속도를 사용한 피치, 롤 변화량
  // 측정 범위 설정에 따라 각도로 변환하기 위해 나누는 값이 다름, 표 32.5 참고
  double X = gyroX / SENSITIVITY, Y = gyroY / SENSITIVITY;

  // 순간 각속도로 각도의 변화량을 계산
  unsigned long time_current = micros();
  double delta = (time_current - time_previous) / 1000000.0;
  gyroPitch = -Y * delta;   // 피치 변화량
  gyroRoll = X * delta;     // 롤 변화량

  time_previous = micros();
}

void readAccelGyroData() {
  Wire.beginTransmission(ADDRESS);  // MPU6050 선택
  Wire.write(0x3B); // X축 방향 가속도 레지스터 선택
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
}
