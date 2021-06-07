int pinLED = 44;       // PA0
boolean LEDstate = false;   // LED 상태

void setup() {
  pinMode(pinLED, OUTPUT);
}

void loop() {
  LEDstate = !LEDstate;     // LED 상태 반전
  digitalWrite(pinLED, LEDstate);

  delay(1000);
}
