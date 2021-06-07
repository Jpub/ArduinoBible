const int INTERVAL = 500;
int pins[] = {12, 13};       // LED 연결 핀

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(pins[i], OUTPUT);     // LED 연결 핀을 출력으로 설정
  }
}

void loop() {
  digitalWrite(pins[0], HIGH);
  digitalWrite(pins[1], LOW);
  delay(INTERVAL);

  digitalWrite(pins[0], LOW);
  digitalWrite(pins[1], HIGH);
  delay(INTERVAL);
}
