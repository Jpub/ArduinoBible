#include <BlinkLED.h>

BlinkLED blink1, blink2;

void setup() {
  blink1.init(13, 1000);
  blink2.init(12, 500);
}

void loop() {
  blink1.update();
  blink2.update();
}
