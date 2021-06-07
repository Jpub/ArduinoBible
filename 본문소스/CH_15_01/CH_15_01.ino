int pin_LED = 3;        // LED 연결 핀

void setup() {
}

void loop() {
  for (int i = 0; i < 255; i++) {     // 점차 밝아짐
    analogWrite(pin_LED, i);
    delay(10);
  }
  for (int i = 255; i > 0; i--) {     // 점차 어두워짐
    analogWrite(pin_LED, i);
    delay(10);
  }
}
