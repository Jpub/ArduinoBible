int LED1 = 13, LED2 = 12;     // LED 연결 핀
boolean state1 = false, state2 = false;   // LED 상태

// 마지막으로 작업을 처리한 시각
unsigned long time_previous1 = 0, time_previous2 = 0;
unsigned long time_current;
int INTERVAL1 = 1000, INTERVAL2 = 500;  // LED 반전 시간 간격

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);
}

void loop() {
  time_current = millis();    // 현재 시각

  blink_1s_task();      // 작업 1 처리 : 1초 간격 블리크
  blink_0_5s_task();      // 작업 2 처리 : 0.5초 간격 블링크
}

void blink_1s_task() {      // 작업 처리 함수 1
  if (time_current - time_previous1 >= INTERVAL1) { // 작업 1 처리 시점 검사
    time_previous1 = time_current;  // 마지막으로 작업 1을 처리한 시각
    state1 = !state1;       // LED 1 상태 반전
    digitalWrite(LED1, state1);     // LED 1 상태 출력
  }
}

void blink_0_5s_task() {      // 작업 처리 함수 2
  if (time_current - time_previous2 >= INTERVAL2) { // 작업 2 처리 시점 검사
    time_previous2 = time_current;  // 마지막으로 작업 2를 처리한 시각
    state2 = !state2;       // LED 2 상태 반전
    digitalWrite(LED2, state2);   // LED 2 상태 출력
  }
}
