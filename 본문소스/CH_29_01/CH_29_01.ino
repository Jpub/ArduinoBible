void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(A0);     // 온도 센서 읽기
  Serial.print("ADC 값 : ");
  Serial.print(String(reading) + ",\t");

  float voltage = reading * 5.0 / 1023.0; // 전압으로 변환
  Serial.print("전압 : ");
  Serial.print(voltage, 2);
  Serial.print(",\t");

  float temperature = voltage * 100;  // ‘전압 * 100’으로 온도 계산
  Serial.print("온도 : ");
  Serial.print(temperature, 2);
  Serial.println(" C");

  delay(1000);
}
