// 0에서 9까지 숫자 표현을 위한 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
};
// 7세그먼트 연결 핀 : a, b, c, d, e, f, g, dp 순서
int pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

int index = 0;        // 현재 출력하는 숫자

void setup() {
  for (int i = 0; i < 8; i++) { // 7세그먼트 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  displayOneDigit(index);       // 숫자 표시

  index = (index + 1) % 10;   // 0~9 반복

  delay(1000);        // 1초 대기
}

void displayOneDigit(byte n) {    // 0~9 사이 숫자 표시
  for (int i = 0; i < 8; i++) { // 7세그먼트에 표시
    boolean on_off = bitRead(patterns[n], i);
    digitalWrite(pins[i], on_off);
  }
}
