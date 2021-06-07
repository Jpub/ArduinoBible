int DATA_PIN = 8;
int LATCH_CLOCK_PIN = 9;
int SHIFT_CLOCK_PIN = 10;

void setup() {
  pinMode(DATA_PIN, OUTPUT);    // 데이터와 제어 핀을 출력으로 설정
  pinMode(LATCH_CLOCK_PIN, OUTPUT);
  pinMode(SHIFT_CLOCK_PIN, OUTPUT);
}

void loop() {
  byte data = 1;

  for (int i = 0; i < 8; i++) {
    digitalWrite(LATCH_CLOCK_PIN, LOW);
    // 8개 비트를 MSB 우선으로 전송하면 74595의 출력 순서와 일치함
    shiftOut(DATA_PIN, SHIFT_CLOCK_PIN, MSBFIRST, data << i);
    // 래치 클록의 상승 에지에서 래치 데이터 출력
    digitalWrite(LATCH_CLOCK_PIN, HIGH);

    delay(500);
  }
}
