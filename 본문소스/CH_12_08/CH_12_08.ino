int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};   // LED가 연결된 핀 배열
byte pattern = 0;     // 표시할 패턴값

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
  randomSeed(analogRead(A0));   // 난수 생성기 초기화
}

void loop() {
  pattern = random(256);    // 0~255 사이 난수 생성
  for (int i = 0; i < 8; i++) {     // LED에 상태 표시
    boolean state = (pattern >> i) & 1; // 비트값 추출
    digitalWrite(pins[i], state);
  }

  delay(500);
}
