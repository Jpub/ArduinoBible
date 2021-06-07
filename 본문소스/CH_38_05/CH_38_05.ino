// 0에서 9까지 숫자 표현을 위한 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
};
// 7세그먼트 연결 핀 : a, b, c, d, e, f, g, dp 순서
int pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int digits[] = { 10, 11, 12, 13 };    // 자리 선택핀 : D1, D2, D3, D4
const int DIGIT_DELAY = 5;

void setup() {
  for (int i = 0; i < 4; i++) {     // 자리 선택핀을 출력으로 설정
    pinMode(digits[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {     // 세그먼트 제어 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  showFourDigitNumber(analogRead(A0));
}

// pos : 출력 위치로 1에서 4 사이 값
// no : 출력할 숫자로 0에서 9 사이 값
void showOneDigitNumber(byte pos, byte no) {
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
    boolean on_off = bitRead(patterns[no], i);
    digitalWrite(pins[i], on_off);
  }
}

void showFourDigitNumber(int number) {
  byte no[4];

  for (int i = 0; i < 4; i++) {     // 각 자릿값을 구함
    no[3 - i] = number % 10;
    number /= 10;
  }

  for (int i = 0; i < 4; i++) {     // 한 자리씩 출력
    showOneDigitNumber(i + 1, no[i]);
    delay(DIGIT_DELAY);
  }
}
