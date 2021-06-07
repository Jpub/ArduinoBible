int pin_LED = 3;        // LED 연결 핀
int pin_vr = A0;        // 가변저항 연결 핀

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화
}

void loop() {
  int value_vr = analogRead(pin_vr);  // 가변저항 값 읽기
  int value_pwm = value_vr >> 2;    // 8비트 듀티 사이클 값으로 변환

  analogWrite(pin_LED, value_pwm);  // PWM 신호 출력

  Serial.print(String("가변저항값 : ") + value_vr);
  Serial.println(String("\tLED 밝기 : ") + value_pwm);

  delay(1000);        // 1초 대기
}
