int PIRpin = 2, LEDpin = 3;
boolean stateLED = false;

void setup() {
  pinMode(PIRpin, INPUT);
  pinMode(LEDpin, OUTPUT);

  digitalWrite(LEDpin, stateLED);

  // 2번 핀의 입력이 변할 때(CHANGE) 자동으로 ISR(turnOnOffLED)가 호출된다.
  attachInterrupt(digitalPinToInterrupt(PIRpin), turnOnOffLED, CHANGE);
}

void turnOnOffLED() {
  stateLED = !stateLED;     // LED 상태 반전
  digitalWrite(LEDpin, stateLED);   // LED 상태 출력
}

void loop() {
  // loop 함수는 비어있다.
}
