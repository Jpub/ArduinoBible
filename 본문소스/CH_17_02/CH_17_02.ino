int LED1 = 13, LED2 = 12;    // LED 연결 핀

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);
}

void loop() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(500);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(500);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(500);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(500);
}
