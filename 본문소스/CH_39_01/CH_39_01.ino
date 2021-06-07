int rows[] = {2, 3, 4, 5, 6, 7, 8, 9};    // 행 연결 핀
int cols[] = {10, 11, 12, 13, A0, A1, A2, A3};    // 열 연결 핀

void setup() {
  for (int i = 0; i < 8; i++) {     // 행과 열 제어 핀을 출력으로 설정
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
}

void clear() {        // 모든 LED를 끔
  for (int i = 0; i < 8; i++) {
    digitalWrite(rows[i], LOW);
    digitalWrite(cols[i], HIGH);
  }
}

void loop() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      clear();

      digitalWrite(rows[row], HIGH);  // row행 col열 LED 켜기
      digitalWrite(cols[col], LOW);

      delay(100);
    }
  }
}
