void setup() {
  Serial.begin(9600);     // 시리얼 포트 초기화

  int n = 1234;
  float f = 3.14159;

  Serial.println(n, BIN);     // 2진수
  Serial.println(n, OCT);     // 8진수
  Serial.println(n, DEC);     // 10진수. 디폴트값으로 DEC는 생략 가능
  Serial.println(n, HEX);     // 16진수

  Serial.println();
  for (int i = 1; i < 6; i++) {
    Serial.println(f, i);     // 소수점 이하 자릿수 지정
  }
}

void loop() {
}
