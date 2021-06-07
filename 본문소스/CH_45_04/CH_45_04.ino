#include <L298N.h>

// 모터 제어 객체 (Enable, Input1, Input2)
L298N motor(10, 9, 8);

void setup() {
}

void loop() {
  for (int i = 0; i < 256; i++) {
    motor.setSpeed(i);      // 속도 설정
    motor.run(L298N::FORWARD);    // 설정한 속도 반영
    delay(30);
  }

  motor.stop();       // 모터 정지

  for (int i = 0; i < 256; i++) {
    motor.run(L298N::BACKWARD);
    motor.setSpeed(i);
    delay(30);
  }
}
