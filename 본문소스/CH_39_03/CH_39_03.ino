int rows[] = {2, 3, 4, 5, 6, 7, 8, 9};     // 행 연결 핀
int cols[] = {10, 11, 12, 13, A0, A1, A2, A3};  // 열 연결 핀

uint16_t smile[] = {      // 사용자 정의 문자 데이터
  0x003C, 0x0042, 0x00A5, 0x0081,
  0x00A5, 0x0099, 0x0042, 0x003C
};

int ROW_DELAY = 2;      // 행 전환 간격
int start_column = 0;     // 표시 시작 칼럼

unsigned long time_previous;
int INTERVAL = 200;     // 열이 움직이는 시간 간격

void setup() {
  for (int i = 0; i < 8; i++) {     // 행과 열 제어 핀을 출력으로 설정
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
  time_previous = millis();
}

void clear() {        // 모든 LED를 끔
  for (int i = 0; i < 8; i++) {
    digitalWrite(rows[i], LOW);
    digitalWrite(cols[i], HIGH);
  }
}

void loop() {
  unsigned long time_current = millis();
  if (time_current - time_previous >= INTERVAL) {
    start_column = (start_column + 1) % 16; // 시작 칼럼 갱신
    time_previous = time_current;
  }

  for (int row = 0; row < 8; row++) {
    clear();
    digitalWrite(rows[row], HIGH);  // 해당 행 선택
    for (int col = 0; col < 8; col++) {
      // start_column부터 8개 칼럼의 데이터 추출
      // 칼럼은 좌우가 연결되어 있음에 주의
      int shift_amount = (31 - start_column - col) % 16;
      // 행 단위 데이터에서 각 열의 데이터 추출
      boolean ox = (smile[row] >> shift_amount) & 0x01;
      // 공통 행 양극 방식으로 켜지는 LED는 LOW를 출력해야 하므로 반전 출력
      digitalWrite(cols[col], !ox);
    }
    delay(ROW_DELAY);
  }
}
