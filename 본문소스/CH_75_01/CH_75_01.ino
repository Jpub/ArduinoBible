const int INTERVAL = 500;    // LED 점멸 간격
int LEDpin = 8;         // LED 연결 핀
boolean LEDstate = false;   // LED 상태

void setup() {
  pinMode(LEDpin, OUTPUT);    // LED 연결 핀을 출력으로 설정
}

void loop() {
  digitalWrite(LEDpin, LEDstate);
  LEDstate = !LEDstate;       // LED 상태 반전
  delay(INTERVAL);
}
