int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};   // LED가 연결된 핀 배열
byte index = 0;         // 표시할 패턴 번호
// 패턴 정의 배열
byte patterns[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {     // LED에 상태 표시
    // 비트 연산으로 바이트 단위 패턴값에서 비트 단위 LED 상태 추출
    boolean state = (patterns[index] >> i) & 1;
    digitalWrite(pins[i], state);
  }

  index = (index + 1) % 8;    // 0~7을 반복
  delay(1000);        // 1초 대기
}
