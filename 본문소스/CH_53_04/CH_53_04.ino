#include <avr/eeprom.h>

void setup() {
  Serial.begin(9600);

  // EEPROM에 쓸 데이터
  uint8_t dataByte = 1;
  uint16_t dataWord = 2;
  uint32_t dataDWord = 3;
  float dataFloat = 3.14;
  char dataString[] = "ABCDE";

  // EEPROM의 주소
  int addressByte = 0, addressWord = 10, addressDWord = 20;
  int addressFloat = 30, addressString = 40;

  // 데이터 쓰기
  eeprom_update_byte ( (uint8_t *)addressByte, dataByte * 10);
  eeprom_update_word ( (uint16_t *)addressWord, dataWord * 10);
  eeprom_update_dword ( (uint32_t *)addressDWord, dataDWord * 10);
  eeprom_update_float ( (float *)addressFloat, dataFloat);
  eeprom_update_block ( (void *)dataString, (void *)addressString, 5);

  // 데이터 읽기
  dataByte = eeprom_read_byte ( (uint8_t *)addressByte );
  dataWord = eeprom_read_word ( (uint16_t *)addressWord );
  dataDWord = eeprom_read_dword ( (uint32_t *)addressDWord );
  dataFloat = eeprom_read_float ( (float *)addressFloat);
  eeprom_read_block ( (void *)dataString, (void *)addressString, 5);

  Serial.println(String("바이트 데이터\t: ") + dataByte);
  Serial.println(String("워드 데이터\t: ") + dataWord);
  Serial.println(String("더블 워드 데이터\t: ") + dataDWord);
  Serial.println(String("실수 데이터\t: ") + dataFloat);
  Serial.println(String("문자열 데이터\t: ") + dataString);
}

void loop() {
}
