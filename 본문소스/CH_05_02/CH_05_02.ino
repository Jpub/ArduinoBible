void setup() {
  Serial.begin(9600);   // 시리얼 통신 초기화, 9600 보율
}

void loop() {
  for (float v = 0; v < 2 * PI; v += 0.1) {
    Serial.print(3 * sin(v)); // 첫 번째 값
    Serial.print(" ");    // 공백문자(스페이스)로 분리
    Serial.print(3 * cos(v)); // 두 번째 값
    Serial.print("\t");   // 공백문자(탭)로 분리
    Serial.println(sin(v) > 0); // 세 번째 값, 이후 개행문자(println)로 행 분리

    delay(10);      // 10 밀리초 대기
  }
}
