#include <SPI.h>

#define EEPROM_READ    0b00000011  // 읽기 명령
#define EEPROM_WREN    0b00000110  // 쓰기 가능 상태 설정 명령
#define EEPROM_WRITE    0b00000010  // 쓰기 명령
#define EEPROM_WRITE_IN_PROGRESS  0 // 쓰기 진행 중 비트 번호
#define EEPROM_RDSR    0b00000101  // 상태 레지스터 읽기 명령

#define EEPROM_PAGE_SIZE    16  // 페이지 크기 (byte)
#define EEPROM_TOTAL_BYTE   128 // 25LC010A 크기 (byte)

void EEPROM_eraseAll(void) {
  uint16_t pageAddress = 0;

  while (pageAddress < EEPROM_TOTAL_BYTE) {
    SPI.beginTransaction( SPISettings() );

    EEPROM_writeEnable();   // 쓰기 가능 모드로 설정

    digitalWrite(SS, LOW);    // EEPROM 선택
    SPI.transfer(EEPROM_WRITE);   // 쓰기 명령 전송
    SPI.transfer(pageAddress);    // 주소 전송
    for (int i = 0; i < EEPROM_PAGE_SIZE; i++) {
      SPI.transfer(0);      // 페이지 단위 데이터 전송
    }
    digitalWrite(SS, HIGH);   // EEPROM 선택 해제

    pageAddress += EEPROM_PAGE_SIZE;  // 페이지 변경
    // 쓰기 완료 대기
    while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS));

    SPI.endTransaction();
  }
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

void EEPROM_writeByte(uint8_t address, uint8_t data) {
  SPI.beginTransaction( SPISettings() );

  EEPROM_writeEnable();     // 쓰기 가능 모드로 설정

  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_WRITE);     // 쓰기 명령 전송
  SPI.transfer(address);      // 주소 전송
  SPI.transfer(data);     // 데이터 전송
  digitalWrite(SS, HIGH); // EEPROM 선택 해제

  // 쓰기가 완료될 때까지 대기
  while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS));

  SPI.endTransaction();
}

uint8_t EEPROM_readByte(uint8_t address) {
  SPI.beginTransaction( SPISettings() );
  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_READ);    // 읽기 명령어 전송
  SPI.transfer(address);      // 메모리 주소 전송
  // 마스터에서 바이트 값을 전송하여야 슬레이브로부터 바이트 값을 받을 수 있다.
  // 전송하는 값은 의미가 없으므로 0을 전송한다.
  byte b = SPI.transfer(0);
  digitalWrite(SS, HIGH);       // EEPROM 선택 해제
  SPI.endTransaction();

  return b;
}

void setup() {
  SPI.begin();        // SPI 초기화
  Serial.begin(9600);     // 시리얼 통신 초기화

  EEPROM_eraseAll();      // EEPROM 내용 삭제

  for (int i = 0; i < 100; i++) {   // 바이트 단위 내용 쓰기
    EEPROM_writeByte(i, i + 50);    // (번지, 값)
  }

  for (int i = 0; i < 100; i++) {   // 바이트 단위 내용 읽기
    byte b = EEPROM_readByte(i);
    Serial.print(String("EEPROM의 ") + i + "번지 내용은 ");
    Serial.println(String(b) + "입니다.");
  }
}

void loop() {
}
