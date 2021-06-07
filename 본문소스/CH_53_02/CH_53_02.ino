#include <EEPROM.h>

typedef union {        // 공용체
  float f;            // 4바이트 단위 읽고 쓰기
  uint8_t b[4];       // 1바이트 단위 읽고 쓰기
} FLOAT;

void setup() {
  Serial.begin(9600);

  write_float_to_EEPROM(1, 3.1415);

  float f = read_float_from_EEPROM(1);

  Serial.print("* EEPROM에 저장된 값은 ");
  Serial.print(f, 4);
  Serial.println("입니다.");
}

void write_float_to_EEPROM(int addr, float no) {
  FLOAT f;

  f.f = no;           // f와 b 필드 값이 모두 바뀜
  for (int i = 0; i < 4; i++) {
    EEPROM.write(addr + i, f.b[i]); // 바이트 단위의 b 필드 값을 나누어 기록

    Serial.print(" => ");
    Serial.print(String(addr + i) + "번지에 ");
    Serial.println(String(f.b[i]) + "을 씁니다.");
  }
  Serial.println();
}

float read_float_from_EEPROM(int addr) {
  FLOAT f;

  for (int i = 0; i < 4; i++) {
    // 바이트 단위로 읽어 b 필드에 기록하면 f 필드 값 역시 바뀜
    f.b[i] = EEPROM.read(addr + i);

    Serial.print(" => ");
    Serial.print(String(addr + i) + "번지에서 ");
    Serial.println(String(f.b[i]) + "을 읽었습니다.");
  }
  Serial.println();

  return f.f;         // 4바이트 실수 반환
}

void loop() {
}
