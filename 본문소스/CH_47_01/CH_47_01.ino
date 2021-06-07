int pins[] = { 8, 9, 10, 11 };     // A, B, /A, /B

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
  for (int i = 0; i < 2048; i++) {    // 2048 스텝으로 1회전 (증가 방향)
    int index = i % 4;
    for (byte j = 0; j < 4; j++) {
      if (j == index) {       // A, B, /A, /B 순서로 하나만 HIGH
        digitalWrite(pins[j], HIGH);
      }
      else {        // 나머지 3개는 LOW
        digitalWrite(pins[j], LOW);
      }
    }
    delay(2);         // 충분한 전력 전달을 위한 대기
  }
}

void backward() {
  for (int i = 2048; i > 0; i--) {    // 2048 스텝으로 1회전 (감소 방향)
    int index = i % 4;
    for (byte j = 0; j < 4; j++) {
      if (j == index) {
        digitalWrite(pins[j], HIGH);
      }
      else {
        digitalWrite(pins[j], LOW);
      }
    }
    delay(2);
  }
}
