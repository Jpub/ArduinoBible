int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  count++;

  Serial.print("* 현재 카운터 값 : ");
  Serial.println(count);

  delay(1000);
}
