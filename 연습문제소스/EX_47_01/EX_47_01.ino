int pins[] = { 8, 9, 10, 11 };     // A, B, /A, /B
byte patterns[8] = {
  0b0001, 0b0011, 0b0010, 0b0110,
  0b0100, 0b1100, 0b1000, 0b1001
};

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);     // 모터 연결 핀을 출력으로 설정
  }
}

void loop() {
  forward();
  delay(500);

  backward();
  delay(500);
}

void forward() {
  for (int i = 0; i < 4096; i++) {    // 2048 스텝으로 1회전 (증가 방향)
    int index = i % 8;
    for (byte j = 0; j < 4; j++) {
      boolean b = (patterns[index] >> j) & 0x01;
      digitalWrite(pins[j], b);
    }
    delay(1);         // 충분한 전력 전달을 위한 대기
  }
}

void backward() {
  for (int i = 4096; i > 0; i--) {    // 2048 스텝으로 1회전 (감소 방향)
    int index = i % 8;
    for (byte j = 0; j < 4; j++) {
      boolean b = (patterns[index] >> j) & 0x01;
      digitalWrite(pins[j], b);
    }
    delay(1);         // 충분한 전력 전달을 위한 대기
  }
}
