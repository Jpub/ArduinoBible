#include <TaskScheduler.h>

void blink1Callback();       // 콜백 함수 원형
void blink2Callback();

Scheduler runner;       // 스케줄러 객체 생성

// 태스크 객체 생성 (시간, 횟수, 콜백, 스케줄러, 활성화)
Task blink1(500, 10, &blink1Callback, &runner, true);
Task blink2(500, 10, &blink2Callback);

int LED1 = 2, LED2 = 3;
boolean state1 = false, state2 = false;

void blink1Callback() {       // 태스크 1의 콜백 함수
  state1 = !state1;
  digitalWrite(LED1, state1);

  if (blink1.isFirstIteration()) {    // 첫 번째 실행
    Serial.println();
    Serial.println("** 태스크 1번의 실행이 시작되었습니다.");
  }
  else if (blink1.isLastIteration()) {    // 마지막 실행
    Serial.println("** 태스크 1번의 실행이 끝났습니다.");

    runner.addTask(blink2);   // 태스크 추가
    blink2.enable();      // 태스크 활성화
    blink2.setInterval(500);    // 실행 간격 설정
    blink2.setIterations(10);   // 실행 횟수 설정

    blink1.disable();     // 태스크 비활성화
    runner.deleteTask(blink1);    // 태스크 삭제

    Serial.println("** 태스크 2번을 스케줄러에 추가하였습니다.");
  }
}

void blink2Callback() {       // 태스크 2의 콜백 함수
  state2 = !state2;
  digitalWrite(LED2, state2);

  if (blink2.isFirstIteration()) {
    Serial.println();
    Serial.println("=> 태스크 2번의 실행이 시작되었습니다.");
  }
  else if (blink2.isLastIteration()) {
    Serial.println("=> 태스크 2번의 실행이 끝났습니다.");

    runner.addTask(blink1);
    blink1.enable();
    blink1.setInterval(500);
    blink1.setIterations(10);

    blink2.disable();
    runner.deleteTask(blink2);

    Serial.println("=> 태스크 1번을 스케줄러에 추가하였습니다.");
  }
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, state1);
  digitalWrite(LED2, state2);

  Serial.begin(9600);
}

void loop() {
  runner.execute();       // 스케줄러 실행
}
