#include <Unistep2.h>

#define STEPS_PER_REV   4096  // 1회전을 위한 스텝 수

// (IN1, IN2, IN3, IN4, 1회전을 위한 스텝 수, 스텝 사이의 지연 시간(us))
Unistep2 stepper(8, 9, 10, 11, STEPS_PER_REV, 900);

int stepTime_old = -1;

void setup() {
}

void loop() {
  stepper.run();

  int vr = analogRead(A0);
  int stepTime = map(vr, 0, 1023, 900, 2000);

  if (stepTime != stepTime_old) {
    stepTime_old = stepTime;

    stepper.setStepTime(stepTime);
  }

  if (stepper.stepsToGo() == 0) {
    stepper.move(STEPS_PER_REV);
  }
}
