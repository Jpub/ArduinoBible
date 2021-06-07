void setup() {
  Serial.begin(9600);

  printOut(PSTR("플래시 메모리 사용을 테스트하고 있습니다.\r\n"));
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
