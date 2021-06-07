int DATA_PIN = 8;
int LATCH_CLOCK_PIN = 9;
int SHIFT_CLOCK_PIN = 10;

// 0에서 9까지 숫자 표현을 위한 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
};

int index = 0;        // 현재 출력하는 숫자
unsigned long time_previous;

void setup() {
  pinMode(DATA_PIN, OUTPUT);    // 데이터와 제어 핀을 출력으로 설정
  pinMode(LATCH_CLOCK_PIN, OUTPUT);
  pinMode(SHIFT_CLOCK_PIN, OUTPUT);

  time_previous = millis();
}

void loop() {
  unsigned long time_current = millis();  // 현재 시각

  if (time_current - time_previous >= 1000) {
    time_previous = time_current;   // 시간 갱신

    index = (index + 1) % 10;     // 0~9 반복
    displayOneDigit(index);     // 숫자 표시
  }
}

void displayOneDigit(byte n) {    // 0~9 사이 숫자 표시
  digitalWrite(LATCH_CLOCK_PIN, LOW);
  // 8개 비트를 MSB 우선으로 전송하면 74595의 출력 순서와 일치함
  shiftOut(DATA_PIN, SHIFT_CLOCK_PIN, MSBFIRST, patterns[n]);
  // 래치 클록의 상승 에지에서 래치 데이터 출력
  digitalWrite(LATCH_CLOCK_PIN, HIGH);
}
