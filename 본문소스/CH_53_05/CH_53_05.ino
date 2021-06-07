void setup() {
  Serial.begin(9600);

  uint8_t *p1 = 0;      // 1바이트 크기 데이터 타입에 대한 포인터
  uint16_t *p2 = 0;     // 2바이트 크기 데이터 타입에 대한 포인터

  Serial.println(String("p1\t : ") + int(p1));
  Serial.println(String("p1 + 1\t : ") + int(p1 + 1));
  Serial.println();

  Serial.println(String("p2\t : ") + int(p2));
  Serial.println(String("p2 + 1\t : ") + int(p2 + 1));
}

void loop() {
}
