#include <SPI.h>

#define EEPROM_READ    0b00000011  // 읽기 명령
#define EEPROM_WREN    0b00000110  // 쓰기 가능 상태 설정 명령
#define EEPROM_WRITE    0b00000010  // 쓰기 명령
#define EEPROM_RDSR    0b00000101  // 상태 레지스터 읽기 명령

#define EEPROM_WRITE_IN_PROGRESS  0 // 쓰기 진행 중 비트 번호

#define EEPROM_PAGE_SIZE    16  // 페이지 크기 (byte)
#define EEPROM_TOTAL_BYTE   128 // 25LC010A 크기 (byte)

void setup() {
  SPI.begin();        // SPI 초기화
  Serial.begin(9600);     // 시리얼 통신 초기화

  // 페이지 단위 쓰기
  SPI.beginTransaction( SPISettings() );

  EEPROM_writeEnable();     // 쓰기 가능 모드로 설정
  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_WRITE);     // 쓰기 명령 전송
  SPI.transfer(0x18);      // 주소 전송
  for (int i = 0; i < 16; i++) {
    SPI.transfer(i);     // 데이터 전송
  }
  digitalWrite(SS, HIGH); // EEPROM 선택 해제

  // 쓰기가 완료될 때까지 대기
  while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS));

  SPI.endTransaction();

  // 페이지 단위 읽기
  SPI.beginTransaction( SPISettings() );

  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_READ);    // 읽기 명령어 전송
  SPI.transfer(0x10);      // 메모리 주소 전송
  for (int i = 0; i < 16; i++) {
    byte b = SPI.transfer(0);
    Serial.print("0x");
    Serial.print(0x10 + i, HEX);
    Serial.println(String(" 번지의 값은 ") + b + " 입니다.");
  }
  SPI.endTransaction();
}

void loop() {
}

uint8_t EEPROM_readStatus(void) {
  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_RDSR);    // 상태 레지스터 읽기 명령 전송
  byte b = SPI.transfer(0);     // 상태 레지스터 값 읽기
  digitalWrite(SS, HIGH);       // EEPROM 선택 해제

  return b;
}

void EEPROM_writeEnable(void) {
  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_WREN);    // 쓰기 가능하도록 설정
  digitalWrite(SS, HIGH);       // EEPROM 선택 해제
}
