// 0에서 9까지 숫자 표현을 위한 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
};
// 7세그먼트 연결 핀 : a, b, c, d, e, f, g, dp 순서
int pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int digits[] = { 10, 11, 12, 13 };    // 자리 선택핀 : D1, D2, D3, D4
const int DIGIT_DELAY = 5;

unsigned long time_previous = 0;
int INTERVAL = 100;     // 시간 업데이트 간격
int count = 0;        // 카운터 값

void showFourDigitNumber(int number,  bool removeLeadingZero = true,
                         byte decimalPoint = 0);

void setup() {
  for (int i = 0; i < 4; i++) {     // 자리 선택핀을 출력으로 설정
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

    count = (count + 1) % 10000;    // 0.0에서 999.9 사이 반복
  }

  // 선행 영은 없애고 세 번째 자리에 소수점 표시
  showFourDigitNumber(count, true, 3);
}

// number : 표시할 4자리 이하 숫자
// removeLeadingZero : 선행 영 제거 여부, 디폴트값은 제거
// decimalPoint : 1~4 사이 소수점 표시 위치, 디폴트값은 0으로 표시 안함
void showFourDigitNumber(int number, bool removeLeadingZero = true,
                         byte decimalPoint = 0) {
  byte no[4];

  for (int i = 0; i < 4; i++) {     // 각 자릿값을 구함
    no[3 - i] = number % 10;
    number /= 10;
  }

  int firstNonZero = 0;       // 배열 인덱스와 같은 0~3 사용
  if (removeLeadingZero) {    // 선행 영 제거 옵션을 선택한 경우
    // 처음으로 영이 아닌 숫자가 나오는 위치를 찾음
    while (firstNonZero < 4 && no[firstNonZero] == 0) {
      firstNonZero++;
    }
    // 모든 자릿값이 0인 경우 한 자리는 0으로 표시
    firstNonZero = (firstNonZero < 3) ? firstNonZero : 3;
    // 소수점 표시가 선택된 경우 소수점 표시 위치부터 영 표시 시작
    if (decimalPoint > 0) {
      if (firstNonZero + 1 > decimalPoint) {
        firstNonZero = decimalPoint - 1;
      }
    }
  }

  for (int i = firstNonZero; i < 4; i++) {  // 한 자리씩 출력
    byte pattern = patterns[no[i]];   // 표시할 숫자의 패턴

    if (i + 1 == decimalPoint) {    // 소수점 표시 위치인 경우
      pattern |= 0x80;      // 패턴에 소수점 패턴 추가
    }
    showOnePattern(i + 1, pattern);   // 패턴값에 의한 7세그먼트 표시
    delay(DIGIT_DELAY);
  }
}

// pos : 출력 위치로 1에서 4 사이 값
// pattern : 출력할 패턴값으로 dp가 MSB, a가 LSB 순서로 저장
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
