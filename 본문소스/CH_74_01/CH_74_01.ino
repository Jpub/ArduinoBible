void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A7);

  Serial.println(String("* 현재 가변저항의 값은 ") + v + "입니다.");

  delay(1000);
}
