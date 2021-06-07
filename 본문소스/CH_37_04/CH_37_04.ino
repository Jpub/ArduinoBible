int pins[] = {8, 9, 10, 11};     // BCD값 출력 핀
int count = 0;        // 현재 출력하는 숫자

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);     // BCD값 출력 핀을 출력으로 설정
  }
  Serial.begin(9600);       // 시리얼 통신 초기화
}

void loop() {
  Serial.print(String(count) + " : ");
  for (int i = 0; i < 4; i++) {     // LSB에서 MSB 순서로 출력
    boolean out = bitRead(count, i);  // BCD값의 각 비트 읽기
    Serial.print(String(out) + " ");

    digitalWrite(pins[i], out);
  }
  Serial.println();       // 줄바꿈
  count = (count + 1) % 10;     // 0~9 사이 반복

  delay(1000);
}
