void setup() {
  Serial.begin(9600);
}

void loop() {
  int ADC_value = analogRead(A0); // 적외선 거리 센서 출력
  float voltage = ADC_value * 5.0 / 1024; // 전압으로 변환

  // 전압을 cm 단위의 거리로 변환
  float distance = 27.86 * pow((double)voltage, -1.15);

  Serial.print("전방 장애물까지 거리 = ");
  Serial.print(distance, 2);
  Serial.println(" cm");

  delay(1000);
}
