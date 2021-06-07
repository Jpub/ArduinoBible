long readAVCC() {
  // AVCC를 기준 전압으로 설정하고 14번 채널 선택
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);           // 채널 안정화 대기

  ADCSRA |= _BV(ADSC);    // AD 변환 시작
  while (bit_is_set(ADCSRA, ADSC)); // 변환 종료 대기

  long result = 1125300L / ADC;   // mV 단위 전압으로 변환
  return result;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(String("현재 AVCC 값은 ") + readAVCC() + String("mV입니다."));
  delay(1000);
}
