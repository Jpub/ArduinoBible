int DATA_PIN = 8;
int LATCH_CLOCK_PIN = 9;
int SHIFT_CLOCK_PIN = 10;

byte data = 0b00000101;

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_CLOCK_PIN, OUTPUT);
  pinMode(SHIFT_CLOCK_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LATCH_CLOCK_PIN, LOW);
  shiftOut(DATA_PIN, SHIFT_CLOCK_PIN, MSBFIRST, data);
  digitalWrite(LATCH_CLOCK_PIN, HIGH);

  data = (data << 1) | (data >> 7);

  delay(500);
}
