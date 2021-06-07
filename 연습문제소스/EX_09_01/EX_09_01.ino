void setup() {
  Serial.begin(9600);

  print_bits(115);
}

void print_bits(uint8_t no) {
  Serial.println(String(no) + "을/를 이진수로 변환했을 때,");
  for (int i = 7; i >= 0; i--) {
    boolean b = (no >> i) & 0x01;

    Serial.println(String(" ") + i + "번 비트는 " + b + "입니다.");
  }
}

void loop() {
}
