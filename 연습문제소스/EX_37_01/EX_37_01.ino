// 0에서 9까지 숫자 표현을 위한 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
};
// 7세그먼트 연결 핀 : a, b, c, d, e, f, g, dp 순서
int pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

int no_previous = -1, no_current;

void setup() {
  for (int i = 0; i < 8; i++) {     // 7세그먼트 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int vr = analogRead(A0);
  no_current = (int)(vr / 102.4);

  if (no_current != no_previous) {
    no_previous = no_current;
    displayOneDigit(no_current);

    Serial.print("7세그먼트에 표시되는 값이 ");
    Serial.println(String(no_current) + "로 바뀌었습니다.");
  }
}

void displayOneDigit(byte n) {    // 0~9 사이 숫자 표시
  for (int i = 0; i < 8; i++) { // 7세그먼트에 표시
    boolean on_off = bitRead(patterns[n], i);
    digitalWrite(pins[i], on_off);
  }
}
