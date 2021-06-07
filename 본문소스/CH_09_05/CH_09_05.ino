void setup() {
  Serial.begin(9600);

  Serial.println(3.14, 8);      // 소수점 이하 8자리 출력
  Serial.println(3.141, 8);
  Serial.println(3.1415, 8);
  Serial.println(3.14159, 8);
  Serial.println(3.141592, 8);
  Serial.println(3.1415926, 8);
  Serial.println(3.14159265, 8);
}

void loop() { }
