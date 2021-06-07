int RGB_LED[] = {9, 10, 11};    // RGB LED 연결 핀

void setup() {
  for (int i = 0; i < 3; i++) {   // LED 연결 핀을 출력으로 설정
    pinMode(RGB_LED[i], OUTPUT);
  }
}

void loop() {
  digitalWrite(RGB_LED[1], HIGH);
  digitalWrite(RGB_LED[2], HIGH);
  for (int i = 255; i >= 0; i--) {    // Blue 색상 조절. Green, Red는 끔
    analogWrite(RGB_LED[0], i);
    delay(10);
  }

  digitalWrite(RGB_LED[0], HIGH);
  digitalWrite(RGB_LED[2], HIGH);
  for (int i = 255; i >= 0; i--) {    // Green 색상 조절. Blue, Red는 끔
    analogWrite(RGB_LED[1], i);
    delay(10);
  }

  digitalWrite(RGB_LED[0], HIGH);
  digitalWrite(RGB_LED[1], HIGH);
  for (int i = 255; i >= 0; i--) {    // Red 색상 조절. Green, Blue는 끔
    analogWrite(RGB_LED[2], i);
    delay(10);
  }
}
