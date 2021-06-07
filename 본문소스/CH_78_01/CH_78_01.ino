void setup() {
  Serial.begin(9600);     // UART0 포트
  Serial1.begin(9600);      // 송신 전용 UART1 포트

}

void loop() {
  if (Serial.available()) {     // 시리얼 모니터에 입력한 데이터
    char ch = Serial.read();

    Serial.write(ch);     // Serial : 시리얼 모니터로 출력
    Serial1.write(ch);      // Serial1 : CoolTerm 터미널로 출력
  }
}
