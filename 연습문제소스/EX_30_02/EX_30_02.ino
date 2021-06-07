#include <Encoder.h>

int pins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

const int MIN_MOVE = 4;
Encoder encoder(3, 2);
long position = 0;
int LED_count = 0;        // LED 개수 (0~8)

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
  }
  Serial.begin(9600);
  show_LED();       // LED 표시
}

void show_LED() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pins[i], i < LED_count);
  }
}

void loop() {
  long newPosition = encoder.read();
  long diff = newPosition - position;

  if (diff >= MIN_MOVE || diff <= -MIN_MOVE) {
    int change = diff / MIN_MOVE;
    LED_count = LED_count + change;

    if (LED_count < 0) {
      LED_count = 0;
    }
    if (LED_count > 8) {
      LED_count = 8;
    }

    if (change > 0) {
      Serial.print("시계방향 회전\t : LED 개수 ");
    }
    else {
      Serial.print("반시계방향 회전\t : LED 개수 ");
    }
    Serial.println(LED_count + String("개"));

    show_LED();

    position = newPosition;
  }
}
