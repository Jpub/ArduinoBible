#include <L298N.h>

// 모터 제어 객체 (Enable, Input1, Input2)
L298N motor(10, 9, 8);

int motorSpeed = 0;      // 모터 속도
boolean motorDirection = true;    // 모터 회전 방향

void setup() {
}

void loop() {
  if (motorDirection) {     // 정회전
    motor.forwardFor(30, motorSpeedChange);
  }
  else {              // 역회전
    motor.backwardFor(30, motorSpeedChange);
  }
}

void motorSpeedChange() {
  motorSpeed++;       // 속도 증가

  // 최고 속도를 넘으면 방향을 바꾸고 속도를 0으로 변경
  if (motorSpeed > 255) {
    motorSpeed = 0;
    motorDirection = !motorDirection;
  }

  motor.reset();        // 다시 움직일 수 있는 상태로 바꿈
  motor.setSpeed(motorSpeed);   // 변경한 속도 적용
}
