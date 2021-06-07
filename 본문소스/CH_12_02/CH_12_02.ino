int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};   // LED가 연결된 핀 배열

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {     // LED 켜기
    digitalWrite(pins[i], HIGH);
  }
  delay(1000);        // 1초 대기

  for (int i = 0; i < 8; i++) {     // LED 끄기
    digitalWrite(pins[i], LOW);
  }
  delay(1000);        // 1초 대기
}
