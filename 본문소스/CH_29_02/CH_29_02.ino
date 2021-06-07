int VCC = 5;          // 아날로그 기준 전압
float R_divide = 4.7;       // 전압 분배를 위한 저항

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(A1);     // 조도 센서 읽기
  Serial.print("ADC 값 : ");
  Serial.print(String(reading) + ",\t");

  float voltage = reading * VCC / 1023.0; // 전압으로 변환
  Serial.print("전압 : ");
  Serial.print(voltage, 2);     // 소수점 이하 2자리 출력
  Serial.print(",\t");

  // 전압 분배에 의해 CdS 센서의 저항값 계산
  float r_cds = R_divide * VCC / voltage - R_divide;
  Serial.print("저항 : ");
  Serial.print(r_cds, 2);
  Serial.println("K");

  delay(1000);
}
