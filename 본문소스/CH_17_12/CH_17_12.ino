int LED1 = 13, LED2 = 12;     // LED 연결 핀
int pin_button = 2;       // 버튼 연결 핀
boolean state1 = false, state2 = false;   // LED 상태

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);
  pinMode(pin_button, INPUT);     // 버튼 연결 핀을 입력으로 설정

  // 디지털 2번 핀의 버튼이 눌러질 때 상승 에지(rising)에서
  // ‘blink’ 함수가 호출되도록 인터럽트 처리 루틴 등록
  attachInterrupt(digitalPinToInterrupt(pin_button), blink, RISING);
}

void loop() {
  state1 = !state1;       // 1초 간격 점멸
  digitalWrite(LED1, state1);

  delay(1000);        // 1초 대기
}

void blink() {
  state2 = !state2;
  digitalWrite(LED2, state2);
}
