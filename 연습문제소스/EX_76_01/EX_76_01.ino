#include <EEPROM.h>

const int MAX_ADDR = 5;    // 기록할 최대 번지

void setup() {
  Serial.begin(9600);

  for (int i = 0; i <= MAX_ADDR; i++) {
    EEPROM.update(i, i * 10);   // EEPROM에 쓰기
    Serial.println(String("EEPROM의 ") + i + "번지에 " + (i * 10) + "을 씁니다.");
  }
  Serial.println();

  for (int i = 0; i <= MAX_ADDR; i++) {
    uint8_t val = EEPROM.read(i);   // EEPROM에서 읽기
    Serial.println(String("EEPROM의 ") + i + "번지 값은 " + val + "입니다.");
  }
}

void loop() {
}
