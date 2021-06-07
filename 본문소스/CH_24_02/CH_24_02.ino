#include <MFRC522.h>

#define RST_PIN   9
#define SS_PIN    10

MFRC522 mfrc522(SS_PIN, RST_PIN);   // MFRC522 객체 생성

void setup() {
  Serial.begin(9600);

  SPI.begin();        // SPI 버스 초기화
  mfrc522.PCD_Init();       // MFRC522 초기화

  mfrc522.PCD_DumpVersionToSerial();  // 리더기 버전 정보
  Serial.println(F("* 카드나 태그를 가까이 가져가세요."));
}

void loop() {
  if ( !mfrc522.PICC_IsNewCardPresent() ) { // 새로운 카드 접근 검사
    return;
  }

  if ( !mfrc522.PICC_ReadCardSerial() ) {   // 카드 선택
    return;
  }

  // UID 출력
  Serial.print(F("Card UID :"));
  dumpByteArrayInHEX(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(String(" (") + mfrc522.uid.size + " 바이트)");
  mfrc522.PICC_HaltA();     // 카드를 정지 상태로 변경
}

void dumpByteArrayInHEX(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
