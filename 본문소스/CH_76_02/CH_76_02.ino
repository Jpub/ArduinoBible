int pinLED = 5;         // PE5, PWM 출력 가능 핀
int vrPin = 52;         // PF7, 아날로그입력 가능 핀

void setup() {
}

void loop() {
  int vrValue = analogRead(vrPin);  // 10비트 아날로그 값 읽기
  int PWMvalue = vrValue >> 2;    // 8비트 PWM 값 만들기

  analogWrite(pinLED, PWMvalue);  // PWM 신호 출력
}
