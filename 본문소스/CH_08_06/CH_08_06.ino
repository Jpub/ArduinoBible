void setup() {
  Serial.begin(9600);     // 시리얼 포트 초기화

  String str = "string ";
  char ar[] = "array ";
  int n = 1234;
  float f = 3.1415;

  String newStr;

  newStr = str + ar;      // String + 문자 배열
  Serial.println(newStr);

  newStr = ar + String(n, BIN);   // 문자 배열 + 정수
  Serial.println(newStr);

  newStr = String(ar) + f;    // 문자 배열 + 실수
  Serial.println(newStr);
}

void loop() {
}
