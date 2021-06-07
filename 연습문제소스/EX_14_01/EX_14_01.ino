int pin_vr = A0;
int pin_LED[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  for (int i = 0; i < 8; i++) {   // LED 연결 핀을 출력으로 설정
    pinMode(pin_LED[i], OUTPUT);
  }
}

void loop() {
  int value = analogRead(pin_vr);   // 가변저항 읽기
  int LEDposition = value >> 7;

  for (int i = 0; i < 8; i++) {
    if (i == LEDposition) {
      digitalWrite(pin_LED[i], HIGH);
    }
    else {
      digitalWrite(pin_LED[i], LOW);
    }
  }
}
