#define _TASK_STATUS_REQUEST
#include <TaskScheduler.h>

int THRESHOLD = 5;

void vrCallback();
void PWMCallback();

Scheduler runner;
StatusRequest request;

// 태스크 객체 생성
Task readAnalog(20, TASK_FOREVER, &vrCallback, &runner, true);
Task blink(&PWMCallback, &runner);

int LED1 = 3;

int vr_old = 0;

void vrCallback() {
  int vr = analogRead(A0);
  if (abs(vr - vr_old) > THRESHOLD) {
    vr_old = vr;
    request.signalComplete(vr);
  }
}

void PWMCallback() {
  int vr = request.getStatus();

  Serial.println(vr);

  analogWrite(LED1, vr >> 2);

  request.setWaiting();
  blink.waitFor(&request);
}

void setup() {
  Serial.begin(9600);

  request.setWaiting();
  blink.waitFor(&request);
}

void loop() {
  runner.execute();
}
