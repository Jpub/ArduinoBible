#include <Stepper.h>

const int stepsPerRevolution = 2048;  // 1회전을 위한 스텝 수

// 모터 드라이브에 연결된 핀 IN1, IN3, IN2, IN4 => A, /A, B, /B 순서
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(15);     // 분당 회전수
}
void loop() {
  myStepper.step(stepsPerRevolution);   // 정회전
  delay(500);

  myStepper.step(-stepsPerRevolution);  // 역회전
  delay(500);
}
