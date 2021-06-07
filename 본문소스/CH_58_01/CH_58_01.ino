#include <TaskScheduler.h>

void blink1Callback();      // 콜백 함수 원형
void blink2Callback();

Scheduler runner;     // 스케줄러 객체 생성

// 태스크 객체 생성 (시간, 횟수, 콜백, 스케줄러, 활성화)
Task blink1(1000, TASK_FOREVER, &blink1Callback, &runner, true);
Task blink2(2000, TASK_FOREVER, &blink2Callback, &runner, true);

int LED1 = 2, LED2 = 3;
boolean state1 = false, state2 = false;

void blink1Callback() {     // 태스크 1의 콜백 함수
  state1 = !state1;
  digitalWrite(LED1, state1);

  Serial.print(String("** 핀 ") + LED1 + "의 LED가 ");
  Serial.println(state1 ? "켜졌습니다." : "꺼졌습니다.");
}

void blink2Callback() {     // 태스크 2의 콜백 함수
  state2 = !state2;
  digitalWrite(LED2, state2);

  Serial.print(String("* 핀 ") + LED2 + "의 LED가 ");
  Serial.println(state2 ? "켜졌습니다." : "꺼졌습니다.");
}

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, state1);
  digitalWrite(LED2, state2);
}

void loop() {
  runner.execute();     // 스케줄러 실행
}
