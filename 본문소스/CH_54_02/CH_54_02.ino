#include <SD.h>

#define SD_CS 10      // SD 카드 Chip/Slave Select

Sd2Card card;
SdVolume volume;
SdFile root;

void setup() {
  Serial.begin(9600);

  Serial.println("* SD 카드를 초기화합니다.");
  SD.begin(SD_CS);

  // 유틸리티 클래스를 이용한 SD 카드 초기화
  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
    Serial.println("** 초기화 과정에서 오류가 발생했습니다.");
    while (1);
  }
  else {
    Serial.println("* 초기화를 완료했습니다.");
  }

  Serial.print("* 카드 종류 : ");   // SD 카드 타입
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:    // SDSC V1
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:    // SDSC V2
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:     // SDHC
      Serial.println("SDHC");
      break;
    default:
      Serial.println("알 수 SD 카드");
  }

  // 볼륨 및 파티션 정보. FAT16이나 FAT32만 지원
  if (!volume.init(card)) {
    Serial.println("* FAT16이나 FAT32 형식의 파일 시스템이 아닙니다.");
    while (1);
  }
  else {            // FAT16 또는 FAT32인 경우
    Serial.print("* 파일 시스템 : FAT");
    Serial.println(volume.fatType());
  }

  float volumeSize;       // SD 카드 크기

  volumeSize = volume.blocksPerCluster();
  volumeSize *= volume.clusterCount();
  volumeSize /= 2;      // 블록 크기는 512 바이트로 2개가 1KB

  volumeSize /= 1024;
  Serial.print("* SD 카드 크기 (MB) : ");
  Serial.println(volumeSize, 2);
  volumeSize /= 1024;
  Serial.print("* SD 카드 크기 (GB) : ");
  Serial.println(volumeSize, 2);

  Serial.println();
  root.openRoot(volume);      // 루트 파일 열기
  // 카드 내 파일과 디렉터리 목록 출력
  // 재귀적 리스팅(LS_R), 마지막 수정 날짜(LS_DATE), 파일 크기(LS_SIZE) 표시
  root.ls(LS_R | LS_DATE | LS_SIZE, 3);
  root.close();
}

void loop() {
}
