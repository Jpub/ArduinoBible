#define _TASK_TIMEOUT
#include <TaskScheduler.h>

void blinkCallback();      // 1초 간격으로 호출
void blinkDisabled();     // 태스크가 비활성화 상태로 바뀔 때 호출

Scheduler runner;

// 태스크 객체 생성 (시간, 횟수, 콜백, 스케줄러, 활성화, 활성화 콜백, 비활성화 콜백)
Task blink(1000, TASK_FOREVER, &blinkCallback, &runner, true,
           NULL, &blinkDisabled);

int LED = 2;
boolean state = false;
int count = 0;

unsigned long time1, time2;

void blinkDisabled() {
  time2 = millis();
  Serial.println("* Blink 태스크가 타임아웃으로 종료되었습니다.");
  Serial.print("  => ");
  Serial.print(time2 - time1);
  Serial.println("밀리초가 경과하였습니다.");
}

void blinkCallback() {
  if (blink.isFirstIteration()) {   // 처음 실행될 때 시간 저장
    time1 = millis();
  }

  Serial.print("* Blink 태스크의 콜백 함수... ");
  Serial.println(count++);

  state = !state;
  digitalWrite(LED, state);
}

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, state);

  blink.setTimeout(10 * TASK_SECOND); // 타임아웃 시간 설정
}

void loop() {
  runner.execute();

  if (!blink.isEnabled()) {     // 비활성 상태인 경우
    count = 0;
    blink.restart();      // 태스크 다시 시작
  }
}
