#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 accelgyro;       // I2C 주소로 디폴트 값 0x68 사용

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  accelgyro.initialize();     // 객체 초기화
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // 데이터 읽기

  Serial.print(ax); Serial.print(' ');
  Serial.print(ay); Serial.print(' ');
  Serial.println(az);

  delay(50);
}
