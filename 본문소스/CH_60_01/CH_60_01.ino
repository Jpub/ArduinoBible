#include <avr/boot.h>

void printIn2HexString(uint8_t val, boolean newLine = true);

void setup() {
  Serial.begin(9600);

  cli();                // 인터럽트 금지
  uint8_t lowByte = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
  uint8_t highByte  = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
  uint8_t extendedByte  = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
  uint8_t lockByte  = boot_lock_fuse_bits_get(GET_LOCK_BITS);
  sei();              // 인터럽트 허용

  Serial.print("Low Fuse\t: 0x");
  printIn2HexString(lowByte);
  Serial.print("High Fuse\t: 0x");
  printIn2HexString(highByte);
  Serial.print("Extended Fuse\t: 0x");
  printIn2HexString(extendedByte);
  Serial.println();
  Serial.print("Lock Byte\t: 0x");
  printIn2HexString(lockByte);
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
