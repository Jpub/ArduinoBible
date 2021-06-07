int pin_LED = 3;        // LED 연결 핀

void setup() {
  pinMode(pin_LED, OUTPUT);   // LED 연결 핀을 출력으로 설정
}

void loop() {
  for (int i = 0; i < 255; i++) {   // 점차 밝아짐
    my_PWM(pin_LED, i);
  }
  for (int i = 255; i > 0; i--) {   // 점차 어두워짐
    my_PWM(pin_LED, i);
  }
}

void my_PWM(int pin, int dim) {
  for (int i = 0; i < 256; i++) {   // 한 주기 내에서
    if (i > dim) {        // LOW인 구간
      digitalWrite(pin, LOW);
    }
    else {            // HIGH인 구간
      digitalWrite(pin, HIGH);
    }
    delayMicroseconds(20);    // 마이크로 초 단위 지연
  }
}
