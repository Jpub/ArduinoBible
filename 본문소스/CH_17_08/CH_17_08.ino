int LED1 = 13;        // LED 연결 핀
boolean state1 = false;     // LED 상태

unsigned long time_previous1 = 0;   // 마지막으로 작업을 처리한 시각
int INTERVAL1 = 1000;     // LED 반전 시간 간격
unsigned long time_current;

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
}

void loop() {
  time_current = millis();      // 현재 시각

  blink_1s_task();      // 작업 처리
}

void blink_1s_task() {      // 작업 처리 함수
  if (time_current - time_previous1 >= INTERVAL1) { // 작업 처리 시점 판단
    time_previous1 = time_current;  // 마지막으로 작업을 처리한 시각
    state1 = !state1;     // LED 상태 반전
    digitalWrite(LED1, state1);   // LED 상태 출력
  }
}
