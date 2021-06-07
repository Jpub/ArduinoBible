int DATA_PIN = 8;
int LATCH_CLOCK_PIN = 9;
int SHIFT_CLOCK_PIN = 10;

void setup() {
  pinMode(DATA_PIN, OUTPUT);    // 데이터와 제어 핀을 출력으로 설정
  pinMode(LATCH_CLOCK_PIN, OUTPUT);
  pinMode(SHIFT_CLOCK_PIN, OUTPUT);

  // 레지스터 내 데이터를 모두 0으로 설정
  digitalWrite(LATCH_CLOCK_PIN, LOW);
  shiftOut(DATA_PIN, SHIFT_CLOCK_PIN, MSBFIRST, 0);
  digitalWrite(LATCH_CLOCK_PIN, HIGH);
}

void loop() {
  digitalWrite(DATA_PIN, HIGH);   // 래치에 기록할 데이터
  for (int i = 0; i < 8; i++) {
    // 상승 에지에서 왼쪽 이동 후 LSB에 DATA 핀 값 추가
    digitalWrite(SHIFT_CLOCK_PIN, LOW);
    digitalWrite(SHIFT_CLOCK_PIN, HIGH);

    // 상승 에지에서 현재 래치의 8비트 값을 출력
    digitalWrite(LATCH_CLOCK_PIN, LOW);
    digitalWrite(LATCH_CLOCK_PIN, HIGH);

    delay(500);
  }

  digitalWrite(DATA_PIN, LOW);    // 래치에 기록할 데이터
  for (int i = 0; i < 8; i++) {
    digitalWrite(SHIFT_CLOCK_PIN, LOW);
    digitalWrite(SHIFT_CLOCK_PIN, HIGH);

    digitalWrite(LATCH_CLOCK_PIN, LOW);
    digitalWrite(LATCH_CLOCK_PIN, HIGH);

    delay(500);
  }
}
