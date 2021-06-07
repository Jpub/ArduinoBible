byte pattern = 0;      // 표시할 패턴값

void setup() {
  // 8개 LED 연결 핀을 출력으로 설정, pinMode 함수에 대응
  DDRD = 0xFF;

  randomSeed(analogRead(A0));   // 난수 생성기 초기화
}

void loop() {
  pattern = random(256);    // 0~255 사이 난수 생성

  // 8개 LED 점멸을 위한 바이트 단위 데이터 출력, digitalWrite 함수에 대응
  PORTD = pattern;

  delay(500);
}
