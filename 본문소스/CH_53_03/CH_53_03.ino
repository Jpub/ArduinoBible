#include <EEPROM.h>

void setup() {
  Serial.begin(9600);

  write_float_to_EEPROM(1, 3.1415);

  float f = read_float_from_EEPROM(1);

  Serial.print("* EEPROM에 저장된 값은 ");
  Serial.print(f, 4);
  Serial.println("입니다.");
}

void write_float_to_EEPROM(int addr, float no) {
  uint8_t *p = (uint8_t*)(&no);   // 바이트 단위 포인터로 변환

  for (int i = 0; i < 4; i++) {   // 바이트 단위 쓰기
    EEPROM.write(addr + i, *(p + i));

    Serial.print(" => ");
    Serial.print(String(addr + i) + "번지에 ");
    Serial.println(String(*(p + i)) + "을 씁니다.");
  }
  Serial.println();
}

float read_float_from_EEPROM(int addr) {
  float no;
  uint8_t *p = (uint8_t*)(&no);   // 바이트 단위 포인터로 변환

  for (int i = 0; i < 4; i++) {   // 바이트 단위 읽기
    *(p + i) = EEPROM.read(addr + i);

    Serial.print(" => ");
    Serial.print(String(addr + i) + "번지에서 ");
    Serial.println(String(*(p + i)) + "을 읽었습니다.");
  }
  Serial.println();

  return no;
}

void loop() {
}
