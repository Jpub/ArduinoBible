int LED1 = 13, LED2 = 12;    // LED 연결 핀
boolean state1 = false, state2 = false; // LED 상태
// 각 LED를 반전시킨 마지막 시간
unsigned long time_previous1 = 0, time_previous2 = 0;

int INTERVAL1 = 1000, INTERVAL2 = 500;  // LED 반전 시간 간격

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);
}

void loop() {
  unsigned long time_current = millis();  // 현재까지의 실행 시간

  if (time_current - time_previous1 >= INTERVAL1) {
    time_previous1 = time_current;
    state1 = !state1;
    digitalWrite(LED1, state1);
  }

  if (time_current - time_previous2 >= INTERVAL2) {
    time_previous2 = time_current;
    state2 = !state2;
    digitalWrite(LED2, state2);
  }
}
