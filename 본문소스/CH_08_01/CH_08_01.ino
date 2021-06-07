void setup() {
  Serial.begin(9600);     // 시리얼 포트 초기화

  Serial.print("String  : ");
  Serial.println("Test String");    // 문자열 출력

  Serial.print("Char    : ");
  Serial.println('c');      // 문자 출력 

  Serial.print("Integer : ");
  Serial.println(123);      // 정수 출력

  Serial.print("Float   : ");
  Serial.println(3.14);     // 실수 출력

  byte data = 65;
  Serial.println();
  Serial.print("With print : ");
  Serial.println(data);     // print 함수

  Serial.print("With write : ");
  Serial.write(data);     // write 함수
}

void loop() {
}
