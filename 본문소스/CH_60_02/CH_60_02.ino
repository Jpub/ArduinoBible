#include <avr/boot.h>

void printIn2HexString(uint8_t val, boolean newLine = true);

void setup() {
  Serial.begin(9600);

  cli();              // 인터럽트 금지
  uint8_t sigByte1 = boot_signature_byte_get(0x000);
  uint8_t sigByte2 = boot_signature_byte_get(0x002);
  uint8_t sigByte3 = boot_signature_byte_get(0x004);

  sei();              // 인터럽트 허용

  Serial.print("Signature Byte : 0x");
  printIn2HexString(sigByte1, false);
  printIn2HexString(sigByte2, false);
  printIn2HexString(sigByte3);
}

// 16진수 두 자리로 출력, newLine으로 줄바꿈 여부를 지정하며 디폴트값으로 줄바꿈
void printIn2HexString(uint8_t val, boolean newLine) {
  Serial.print(val / 16, HEX);
  Serial.print(val % 16, HEX);
  if (newLine) {
    Serial.println();
  }
}

void loop() {
}
