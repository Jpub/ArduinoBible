void setup() {
  Serial.begin(9600);

  uint8_t data1[] = { 10, 20, 30 };   // 1바이트 크기 데이터 배열
  uint16_t data2[] = { 100, 200, 300 }; // 2바이트 크기 데이터 배열

  int address1 = 0, address2 = 100; // EEPROM 주소

  for (int i = 0; i < 3; i++) {   // 1바이트 크기 데이터 배열 쓰기
    eeprom_update_byte ( (uint8_t *)address1 + i, data1[i]);
    // eeprom_update_byte ( (uint8_t *)(address1 + i), data1[i]);
  }

  for (int i = 0; i < 3; i++) {   // 2바이트 크기 데이터 배열 쓰기
    eeprom_update_word ( (uint16_t *)address2 + i, data2[i]);
    // eeprom_update_word ( (uint16_t *)(address2 + i * 2), data2[i]);
  }

  uint8_t dataByte;
  uint16_t dataWord;

  for (int i = 0; i < 3; i++) {   // 1바이트 크기 데이터 배열 읽기
    dataByte = eeprom_read_byte ( (uint8_t *)address1 + i );
    // dataByte = eeprom_read_byte ( (uint8_t *)(address1 + i) );

    Serial.print(String("uint8_t 타입 배열의 ") + i + "번째 값 : ");
    Serial.println(dataByte);
  }
  Serial.println();

  for (int i = 0; i < 3; i++) {   // 2바이트 크기 데이터 배열 읽기
    dataWord = eeprom_read_word ( (uint16_t *)address2 + i );
    // dataWord = eeprom_read_word ( (uint16_t *)(address2 + i * 2) );
    Serial.print(String("uint16_t 타입 배열의 ") + i + "번째 값 : ");
    Serial.println(dataWord);
  }
}

void loop() {
}
