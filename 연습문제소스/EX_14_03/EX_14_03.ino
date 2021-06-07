void setup() {
  Serial.begin(9600);
}

void loop() {
  int value1 = read_analog_pin(A0);
  int value2 = read_analog_pin(A1);

  Serial.println(String("   ( \t") + value1 + ",\t" + value2 + " )");
  delay(1000);        // 1초 대기
}

int read_analog_pin(int no){
  analogRead(no);
  delay(10);
  return analogRead(no);
}
