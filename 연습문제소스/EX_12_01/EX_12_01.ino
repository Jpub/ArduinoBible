int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};
byte pattern = 0xA0;

byte circular_shift_right(byte p, byte n) {
  return (p >> n) | (p << (8 - n));
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {
    boolean state = (pattern >> i) & 1;
    digitalWrite(pins[i], state);
  }

  pattern = circular_shift_right(pattern, 1);
  delay(1000);
}
