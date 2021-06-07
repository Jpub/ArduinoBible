#include <EEPROM.h>

void setup() {
  Serial.begin(9600);

  write_float_to_EEPROM(1, 3.1415);

  float f = read_float_from_EEPROM(1);
}

void write_float_to_EEPROM(int addr, float no) {
  void *data = (void*)(&no);
  
  eeprom_write_block ( data, (void *)addr, 4);

  Serial.print(String("* EEPROM의 ") + addr + " 번지에 ");
  Serial.print(no, 4);
  Serial.println(" 값을 씁니다.");
}

float read_float_from_EEPROM(int addr) {
  float no;
  
  eeprom_read_block ( (void *)(&no), (void *)addr, 4);

  Serial.print(String("* EEPROM의 ") + addr + " 번지에서 ");
  Serial.print(no, 4);
  Serial.println(" 값을 읽었습니다.");

  return no;
}

void loop() {
}
