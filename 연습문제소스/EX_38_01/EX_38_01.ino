// 0에서 9까지 숫자 표현을 위한 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {
  0b00111110, 0b00111101, 0b00111011, 0b00110111, 0b00101111, 0b00011111
};
// 7세그먼트 연결 핀 : a, b, c, d, e, f, g, dp 순서
int pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int digits[] = { 10, 11, 12, 13 };    // 자릿수 선택핀 : D1, D2, D3, D4
const int DIGIT_DELAY = 5;
byte startIndex = 0;

unsigned long time_previous = 0;
int INTERVAL = 500;      // 시간 업데이트 간격

void setup() {
  for (int i = 0; i < 4; i++) {     // 자릿수 선택핀을 출력으로 설정
    pinMode(digits[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {     // 세그먼트 제어 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  unsigned long time_current = millis();
  if (time_current - time_previous >= INTERVAL) {
    time_previous = time_current;

    startIndex = (startIndex + 1) % 6;
  }

  // 선행 영은 없애고 세 번째 자리에 소수점 표시
  showFourPatterns(startIndex);
}

void showFourPatterns(byte index) {
  for (int i = 0; i < 4; i++) {
    showOnePattern(i + 1, patterns[(index + i) % 6]);
    delay(DIGIT_DELAY);
  }
}

void showOnePattern(byte pos, byte pattern) {
  for (int i = 0; i < 4; i++) {     // 자리 선택을 모두 해제
    digitalWrite(digits[i], HIGH);
  }
  for (int i = 0; i < 8; i++) {   // 모든 세그먼트를 끔
    digitalWrite(pins[i], LOW);
  }

  for (int i = 0; i < 4; i++) {     // 공통 음극 방식
    if (i + 1 == pos) {       // 해당 자릿수의 선택 핀만 LOW로 설정
      digitalWrite(digits[i], LOW);
    }
  }
  for (int i = 0; i < 8; i++) {     // 8개 세그먼트 제어로 숫자 표시
    boolean on_off = bitRead(pattern, i);
    digitalWrite(pins[i], on_off);
  }
}
