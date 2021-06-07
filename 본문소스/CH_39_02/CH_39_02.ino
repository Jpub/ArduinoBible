int rows[] = {2, 3, 4, 5, 6, 7, 8, 9};    // 행 연결 핀
int cols[] = {10, 11, 12, 13, A0, A1, A2, A3};  // 열 연결 핀

byte smile[] = {        // 사용자 정의 문자 데이터
  B00111100, B01000010, B10100101, B10000001,
  B10100101, B10011001, B01000010, B00111100
};

int ROW_DELAY = 2;      // 행 전환 간격

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
    clear();
    digitalWrite(rows[row], HIGH);  // 해당 행 선택
    for (int col = 0; col < 8; col++) {
      // 행 단위 데이터에서 각 열의 데이터 추출
      boolean ox = (smile[row] >> (7 - col)) & 0x01;
      // 공통 행 양극 방식으로 켜지는 LED는 LOW를 출력해야 하므로 반전 출력
      digitalWrite(cols[col], !ox);
    }
    delay(ROW_DELAY);
  }
}
