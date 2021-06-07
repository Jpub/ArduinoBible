boolean state = false;      // LED 상태

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // LED 연결 핀을 출력으로 설정
}

void loop() {
  digitalWrite(LED_BUILTIN, state);   // LED 연결 핀으로 상태 출력
  state = !state;
  delay(1000);        // 1초 대기
}
