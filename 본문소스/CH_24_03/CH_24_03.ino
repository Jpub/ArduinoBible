#include <MFRC522.h>

#define RST_PIN   9
#define SS_PIN    10

MFRC522 mfrc522(SS_PIN, RST_PIN); // MFRC522 객체 생성
MFRC522::MIFARE_Key key;    // 인증 키

void setup() {
  Serial.begin(9600);

  SPI.begin();        // SPI 버스 초기화
  mfrc522.PCD_Init();       // MFRC522 초기화

  // 초깃값 0xFFFFFFFFFFFF를 Key A 값으로 사용
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  randomSeed(analogRead(A0));     // 난수 발생기 초기화

  Serial.println("** 1번 섹터 4번 데이터 블록에 랜덤 데이터를 씁니다.");
  Serial.println("** 카드나 태그를 가까이 가져가세요.");
  Serial.println();
}

void loop() {
  if ( !mfrc522.PICC_IsNewCardPresent() ) { // 새로운 카드 접근 검사
    return;
  }

  if ( !mfrc522.PICC_ReadCardSerial() ) {     // 카드 선택
    return;
  }

  // UID 출력
  Serial.println("* 새로운 카드가 발견되었습니다.");
  Serial.print(" => Card UID\t:");
  dumpByteArrayInHEX(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(String(" (") + mfrc522.uid.size + " 바이트)");

  Serial.print(" => PICC type\t: ");
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  if (piccType != MFRC522::PICC_TYPE_MIFARE_1K
      && piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(" => MIFARE 1K나 4K 카드만 사용할 수 있습니다.");
    return;
  }
  else {
    Serial.println(" => 사용할 수 있는 카드입니다.");
  }

  byte sector = 1;      // 1번 섹터의 4번~7번 블록 중
  byte blockAddr = 4;       // 4번 블록에 씀
  byte dataBlock[16];     // 쓰기 데이터

  byte trailerBlock = 7;
  MFRC522::StatusCode status;
  byte buffer[18];      // 블록 데이터 읽기 버퍼
  byte size = sizeof(buffer);

  // Key A를 사용한 인증
  Serial.println("* Key A를 사용하여 인증을 진행합니다.");
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(
             MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(" => 인증에 실패했습니다.");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else {
    Serial.println(" => 인증에 성공했습니다.");
  }
  Serial.println();

  printSectorData(sector);    // 현재 섹터 데이터 출력

  // 4번 데이터 블록 읽기
  Serial.println(String("* 블록 ") + blockAddr + "번 데이터를 읽습니다.");
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(" => 데이터 읽기에 실패했습니다 : ");
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  else {
    Serial.print(String(" => 블록 ") + blockAddr + "번 데이터 : ");
    dumpByteArrayInHEX(buffer, 16);
    Serial.println();
  }

  Serial.println("* 블록에 쓸 데이터를 생성합니다.");
  for (int i = 0; i < 16; i++) {    // 랜덤 데이터 생성
    dataBlock[i] = random(0, 256);
  }
  Serial.print(" => 랜덤 데이터 : ");
  dumpByteArrayInHEX(dataBlock, 16);
  Serial.println();

  // 4번 데이터 블록에 쓰기
  Serial.println(String("* 블록 ") + blockAddr + "번에 데이터를 씁니다.");
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(" => 데이터 쓰기에 실패했습니다 : ");
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  else {
    Serial.println(" => 데이터 쓰기에 성공했습니다.");
  }

  // 4번 데이터 블록 다시 읽기
  Serial.println(String("* 블록 ") + blockAddr + "번 데이터을 다시 읽습니다.");
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(" => 데이터 읽기에 실패했습니다 : ");
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  else {
    Serial.print(String(" => 블록 ") + blockAddr + "번 데이터 : ");
    dumpByteArrayInHEX(buffer, 16);
    Serial.println();

    Serial.println("* 쓴 데이터와 읽은 데이터를 비교합니다.");

    bool resultOK = true;
    for (byte i = 0; i < 16; i++) {
      if (buffer[i] != dataBlock[i]) {
        resultOK = false;
        break;
      }
    }

    if (resultOK) {
      Serial.println(" => 데이터 검증에 성공했습니다.");
    }
    else {
      Serial.println(" => 데이터 검증에 실패했습니다.");
    }
    Serial.println();
  }

  printSectorData(sector);    // 현재 섹터 데이터 출력

  mfrc522.PICC_HaltA();       // 카드를 정지 상태로 변경
  mfrc522.PCD_StopCrypto1();    // 인증 종료
}

void printSectorData(int sector) {
  Serial.println("* 현재 섹터 데이터");
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  Serial.println();
}

void dumpByteArrayInHEX(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
