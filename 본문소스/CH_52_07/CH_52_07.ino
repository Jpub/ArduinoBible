int pinLED = 13, pinButton = 2;
boolean state = false;       // LED 상태

void blink() {
  state = !state;         // LED 상태 반전
}

void setup() {
  pinMode(pinLED, OUTPUT);

  // 디지털 2번 핀의 버튼이 눌러질 때 상승 에지(rising)에서
  // 'blink' 함수가 호출되도록 인터럽트 처리 루틴 등록
  attachInterrupt(digitalPinToInterrupt(pinButton), blink, RISING);
}

void loop() {
  digitalWrite(pinLED, state);    // LED 상태 표시
}
