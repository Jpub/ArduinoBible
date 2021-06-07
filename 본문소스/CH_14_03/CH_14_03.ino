int pin_vr = A0;       // 가변저항 연결 핀
int pin_LED[] = {2, 3, 4, 5, 6, 7, 8, 9}; // LED 연결 핀 배열

void setup() {
  Serial.begin(9600);       // 시리얼 통신 초기화
  for (int i = 0; i < 8; i++) {   // LED 연결 핀을 출력으로 설정
    pinMode(pin_LED[i], OUTPUT);
  }
}

void loop() {
  int value = analogRead(pin_vr);   // 가변저항 읽기
  // 가변저항 값을 LED 개수로 변환
  int LEDcount = map(value, 0, 1023, 0, 8);

  for (int i = 0; i < 8; i++) {
    if (i < LEDcount) {
      digitalWrite(pin_LED[i], HIGH);
    }
    else {
      digitalWrite(pin_LED[i], LOW);
    }
  }

  Serial.print(String("가변저항 : ") + value);
  Serial.println(String("\tLED 개수 : ") + LEDcount);

  delay(500);         // 0.5초 대기
}
