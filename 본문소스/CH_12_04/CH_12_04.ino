int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};   // LED가 연결된 핀 배열
boolean state = false;      // LED 상태

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  state = !state;         // LED 상태 반전
  for (int i = 0; i < 8; i++) {     // LED에 상태 표시
    digitalWrite(pins[i], state);
  }
  delay(1000);        // 1초 대기
}
