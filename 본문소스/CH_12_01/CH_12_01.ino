void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // LED 연결 핀을 출력으로 설정
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // LED 켜기
  delay(1000);        // 1초 대기
  digitalWrite(LED_BUILTIN, LOW); // LED 끄기
  delay(1000);        // 1초 대기
}
