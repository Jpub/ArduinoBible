#include <SPI.h>

#define EEPROM_READ    0b00000011  // 읽기 명령
#define EEPROM_WREN    0b00000110  // 쓰기 가능 상태 설정 명령
#define EEPROM_WRITE   0b00000010  // 쓰기 명령
#define EEPROM_RDSR    0b00000101  // 상태 레지스터 읽기 명령

#define EEPROM_WRITE_IN_PROGRESS  0 // 쓰기 진행 중 비트 번호

void setup() {
  Serial.begin(9600);
  SPI.begin();

  // 2바이트 크기 정수 쓰기
  for (int i = 1000; i < 1010; i += 2) {
    EEPROM_writeInt(i - 1000, i);
  }

  // 2바이트 크기 정수 읽기
  for (int i = 0; i < 10; i += 2) {
    int value = EEPROM_readInt(i);
    Serial.print("0x0");
    Serial.print(i, HEX);
    Serial.println(String(" 번지의 값은 ") + value + "입니다.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

int EEPROM_readInt(uint8_t address) {
  SPI.beginTransaction( SPISettings() );
  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_READ);    // 읽기 명령어 전송
  SPI.transfer(address);      // 메모리 주소 전송
  // 마스터에서 바이트 값을 전송하여야 슬레이브로부터 바이트 값을 받을 수 있다.
  // 전송하는 값은 의미가 없으므로 0을 전송한다.
  int b = SPI.transfer16(0);
  digitalWrite(SS, HIGH);       // EEPROM 선택 해제
  SPI.endTransaction();

  return b;
}

void EEPROM_writeEnable(void) {
  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_WREN);    // 쓰기 가능하도록 설정
  digitalWrite(SS, HIGH);       // EEPROM 선택 해제
}

void EEPROM_writeInt(uint8_t address, int data) {
  SPI.beginTransaction( SPISettings() );

  EEPROM_writeEnable();     // 쓰기 가능 모드로 설정

  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_WRITE);     // 쓰기 명령 전송
  SPI.transfer(address);      // 주소 전송
  SPI.transfer16(data);     // 데이터 전송
  digitalWrite(SS, HIGH); // EEPROM 선택 해제

  // 쓰기가 완료될 때까지 대기
  while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS));

  SPI.endTransaction();
}

uint8_t EEPROM_readStatus(void) {
  digitalWrite(SS, LOW);      // EEPROM 선택
  SPI.transfer(EEPROM_RDSR);    // 상태 레지스터 읽기 명령 전송
  byte b = SPI.transfer(0);     // 상태 레지스터 값 읽기
  digitalWrite(SS, HIGH);       // EEPROM 선택 해제

  return b;
}
