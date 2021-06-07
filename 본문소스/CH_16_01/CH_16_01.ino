#include <EEPROM.h>

int address = 10;      // EEPROM의 주소

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화
  int value = 100;      // EEPROM에 기록할 값

  Serial.print(String("EEPROM의 ") + address + "번지에 ");
  Serial.println(String(value) + "의 값을 씁니다.");
  EEPROM.write(address, value);   // EEPROM에 쓰기

  value = EEPROM.read(address);   // EEPROM에서 읽기
  Serial.print(String("EEPROM의 ") + address + "번지에서 읽은 값은 ");
  Serial.println(String(value) + "입니다.");
}

void loop() {
}
