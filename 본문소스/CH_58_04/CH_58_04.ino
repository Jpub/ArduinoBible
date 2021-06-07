#define _TASK_STATUS_REQUEST  // StatusRequest 클래스 사용
#include <TaskScheduler.h>

void blink1Callback();
void blink2Callback();

StatusRequest request;
Scheduler runner;

// 태스크 객체 생성 (시간, 횟수, 콜백, 스케줄러, 활성화)
Task blink1(1000, TASK_FOREVER, &blink1Callback, &runner, true);
Task blink2(&blink2Callback, &runner);

int LED1 = 2, LED2 = 3;
boolean state1 = false, state2 = true;
byte requestCode = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, state1);
  digitalWrite(LED2, state2);

  request.setWaiting();   // StatusRequest 객체의 카운터 값을 1로 설정
  blink2.waitFor(&request); // 태스크 2를 대기 상태로 설정
}

void blink1Callback() {
  Serial.println("* Blink 1 태스크의 콜백 함수...");

  state1 = !state1;
  digitalWrite(LED1, state1);

  requestCode = (requestCode + 1) % 2;
  // StatusRequest 객체의 카운터 값을 0으로 설정하고 1 또는 2 상태 코드 전달
  request.signalComplete(requestCode + 1);
}

void blink2Callback() {   // StatusRequest 객체의 카운터 값이 0일 때 호출
  // StatusRequest 객체의 상태 코드 확인
  int requestState = request.getStatus();

  Serial.print("* Blink 2 태스크의 콜백 함수 : ");
  Serial.println(requestState);

  if (requestState == 1) {    // 상태 코드가 1인 경우에만 LED 점멸
    state2 = !state2;
    digitalWrite(LED2, state2);
  }

  request.setWaiting();   // StatusRequest 객체의 카운터 값을 1로 설정
  blink2.waitFor(&request); // 태스크 2를 대기 상태로 설정
}

void loop() {
  runner.execute();
}
