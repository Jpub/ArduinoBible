const char str[] PROGMEM = "같은 문자열을 출력하고 있습니다.\r\n";

void setup() {
  Serial.begin(9600);

  printOut(str);
  printOut(str);
}

void loop() {
}

void printOut(const char *str) {
  char ch = pgm_read_byte(str);
  while (ch) {
    Serial.write(ch);
    str++;
    ch = pgm_read_byte(str);
  }
}
