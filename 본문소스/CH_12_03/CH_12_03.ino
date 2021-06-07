int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};   // LED가 연결된 핀 배열

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void control_LED(boolean state) {
  for (int i = 0; i < 8; i++) {     // LED에 상태 표시
    digitalWrite(pins[i], state);
  }
}

void loop() {
  control_LED(true);      // LED 켜기
  delay(1000);        // 1초 대기

  control_LED(false);     // LED 끄기
  delay(1000);        // 1초 대기
}
