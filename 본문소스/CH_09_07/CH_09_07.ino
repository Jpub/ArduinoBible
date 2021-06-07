void setup() {
  Serial.begin(9600);
}

void loop() {
  int A = 0;          // 지역(local) 변수
  static int B = 0;     // 정적(static) 변수

  A = A + 1;
  B = B + 1;

  Serial.println(String("A = ")  + A + ",\tB = " + B);
  delay(1000);        // 1초 대기
}
