int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};   // LED가 연결된 핀 배열
byte pattern = 0x01;      // 표시할 패턴값

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {     // LED에 상태 표시
    // 비트 연산으로 바이트 단위 패턴값에서 비트 단위 LED 상태 추출
    boolean state = (pattern >> i) & 1;
    digitalWrite(pins[i], state);
  }

  pattern = circular_shift_left(pattern, 1);  // 1비트 왼쪽 원형 이동
  delay(100);         // 1초 대기
}

byte circular_shift_left(byte p, byte n) {  // p를 n비트 왼쪽으로 원형 이동
  return (p << n) | (p >> (8 - n));
}
