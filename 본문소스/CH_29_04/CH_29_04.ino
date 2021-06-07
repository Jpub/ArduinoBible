int VCC = 5;         // 아날로그 기준 전압
float R_divide = 10.0;      // 전압 분배를 위한 저항

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(A3);     // 휨 센서 읽기
  Serial.print("ADC 값 : ");
  Serial.print(String(reading) + ",\t");

  float voltage = reading * VCC / 1023.0; // 전압으로 변환
  Serial.print("전압 : ");
  Serial.print(voltage, 2);
  Serial.print(",\t");

  // 전압 분배에 의해 휨 센서의 저항값 계산
  float r_flex = R_divide * VCC / voltage - R_divide;
  Serial.print("저항 : ");
  Serial.print(r_flex, 2);
  Serial.println("K");

  delay(1000);
}
