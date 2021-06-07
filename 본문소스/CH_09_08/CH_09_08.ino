void setup() {
  Serial.begin(9600);

  int n1 = 10, n2 = 3;      // 정수형 변수
  float f1 = 10.0, f2 = 3.0;    // 실수형 변수

  Serial.println(String("몫 : ") + (n1 / n2) + ", 나머지 : " + (n1 % n2));

  Serial.println();
  Serial.println(String("정수 / 정수 : ") + (n1 / n2));
  Serial.println(String("정수 / 실수 : ") + (n1 / f2));
  Serial.println(String("실수 / 정수 : ") + (f1 / n2));
  Serial.println(String("실수 / 실수 : ") + (f1 / f2));
}

void loop() { }
