const float value[] PROGMEM = {
  1.23, 2.34, 3.45, 4.56
};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    Serial.println(pgm_read_float(value + i));
  }
}

void loop() {
}
