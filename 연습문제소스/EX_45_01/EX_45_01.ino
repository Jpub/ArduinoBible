#include <L298N.h>

// 모터 제어 객체 (Enable, Input1, Input2)
L298N motor(10, 9, 8);

void setup() {
}

void loop() {
  int motorSpeed = analogRead(A0) >> 2;

  motor.setSpeed(motorSpeed);      // 속도 설정
  motor.run(L298N::FORWARD);    // 설정한 속도 반영
  delay(30);
}
