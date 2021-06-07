int count = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);      // 시리얼 포트가 준비되기를 기다림
}

void loop() {
  Serial.print("현재 카운터 값은 ");   // 카운터 값 출력
  Serial.print(count++);
  Serial.println("입니다.");

  delay(1000);
}
