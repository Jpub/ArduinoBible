int LED1 = 13;        // LED 연결 핀
boolean state1 = false;     // LED 상태

int INTERVAL1 = 1000;     // LED 반전 시간 간격

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
}

void loop() {
  state1 = !state1;       // LED 상태 반전
  digitalWrite(LED1, state1);   // LED 상태 출력
  delay(INTERVAL1);
}
