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

  if ( !mfrc522.PICC_ReadCardSerial() ) {     // 카드 선택
    return;
  }

  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  // 카드 정보 출력
}
