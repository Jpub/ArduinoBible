void setup() {
  Serial.begin(9600);

  int A = 1;
  int B[4] = { 11, 12, 13, 14 };    // 배열 선언 시에만 한꺼번에 초기화 가능

  // 일반 변수가 저장된 메모리 주소
  Serial.print("변수 A가 저장된 메모리 주소\t\t: ");
  Serial.println(unsigned(&A), HEX);  // 16진수로 출력

  // 배열 변수가 저장된 메모리 주소
  for (int i = 0; i < 4; i++) {
    Serial.print("변수 B[" + String(i) + "]가 저장된 메모리 주소\t: ");
    Serial.println(unsigned(&B[i]), HEX); // 16진수로 출력
  }
}

void loop() { }
