void setup() {
  Serial.begin(9600);

  char str[] = "String";      // 문자열 끝을 위한 NULL 문자 추가
  int no[] = { 1, 2, 3, 4 };    // 배열 끝을 위한 표시 없음

  Serial.print("문자 배열에 할당된 메모리 크기 \t: ");
  Serial.println(sizeof(str));

  Serial.print("정수 배열에 할당된 메모리 크기 \t: ");
  Serial.println(sizeof(no));
}

void loop() { }
