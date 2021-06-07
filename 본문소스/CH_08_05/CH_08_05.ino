void setup() {
  Serial.begin(9600);       // 시리얼 포트 초기화

  String str;         // String 객체
  char c = 'A';
  int n = 1234;
  float f = 3.1415;

  str = "character array";    // 문자 배열로부터 생성
  Serial.println(str);      // 문자열 출력

  str = c;            // 문자로부터 생성
  Serial.println(str);

  // str = n;         // 10진 문자열만 가능
  str = String(n, BIN);     // 2진 문자열 생성
  Serial.println(str);

  // str = f;         // 소수점 이하 2자리만 가능
  str = String(f, 4);     // 소수점 이하 4자리 실수 문자열 생성
  Serial.println(str);
}

void loop() {
}
