int count = 0;

void setup() {
  Serial.begin(9600);

  int v = 123;
  Serial.printf("8진수 = %o, 10진수 = %d, 16진수 = 0x%X\n", v, v, v);

  Serial.printf("일반 출력 \t\t:|%d|\n", v);
  Serial.printf("오른쪽 정렬 \t:|%5d|\n", v);
  Serial.printf("왼쪽 정렬 \t\t:|%-5d|\n", v);
}

void loop() {
}
