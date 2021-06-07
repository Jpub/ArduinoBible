uint8_t buffer[8] = { 0, };      // 문자 정보 전달 버퍼

void setup() {
  Serial.begin(9600);     // UART 시리얼 통신 초기화
}

void key_press(uint8_t ch) {
  buffer[2] = ch;       // 키 누름 정보
  // ATmega328에서 ATmega16u2로 UART 시리얼 통신 사용
  Serial.write(buffer, 8);
  delay(10);          // 키 누름 지연
}

void key_release() {
  buffer[0] = 0;        // 키 뗌 정보
  buffer[2] = 0;
  Serial.write(buffer, 8);
}

void loop() {
  key_press(11);        // 'h'
  key_release();
  key_press(8);         // 'e'
  key_release();
  key_press(15);        // 'l'
  key_release();
  key_press(15);        // 'l'
  key_release();
  key_press(18);        // 'o'
  key_release();
  key_press(40);        // ENTER
  key_release();

  delay(1000);
}
