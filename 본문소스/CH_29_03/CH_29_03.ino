int pins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };  // LED 연결 핀

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화

  for (int i = 0; i < 8; i++) {   // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  int reading = analogRead(A2);     // 압력 센서 읽기

  // 나누는 값 100은 그림 29.14의 결과를 바탕으로 결정한 것이다.
  int LED_count = reading / 100;
  LED_count = LED_count % 9;    // 0~8개 LED로 제한

  Serial.print("ADC 값 : ");
  Serial.print(String(reading) + ",\tLED 개수 : ");
  Serial.println(LED_count);

  for (int i = 0; i < 8; i++) {   // 압력에 따라 LED 개수 제어
    boolean onoff = i < LED_count;
    digitalWrite(pins[i], onoff);
  }

  delay(1000);
}
