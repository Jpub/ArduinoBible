void setup() {
  Serial.begin(9600);

  Serial.println(String("정수형 일반 변수\t : ") + sizeof(int));
  Serial.println(String("실수형 일반 변수\t : ") + sizeof(float));
  Serial.println(String("문자형 일반 변수\t : ") + sizeof(char));

  Serial.println();
  Serial.println(String("정수형 포인터 변수\t : ") + sizeof(int*));
  Serial.println(String("실수형 포인터 변수\t : ") + sizeof(float*));
  Serial.println(String("문자형 포인터 변수\t : ") + sizeof(char*));
}

void loop() { }
