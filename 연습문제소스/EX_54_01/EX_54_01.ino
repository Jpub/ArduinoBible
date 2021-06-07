#include <SD.h>
#define SD_CS 10      // SD 카드 Chip/Slave Select

void setup() {
  Serial.begin(9600);

  Serial.println("* SD 카드를 초기화합니다.");
  if (!SD.begin(SD_CS)) {     // SD 카드 초기화
    Serial.println("** 초기화 과정에서 오류가 발생했습니다.");
    while (1);
  }
  Serial.println("* 초기화를 완료했습니다.");
  Serial.println("* 파일과 디렉터리 삭제를 시작합니다.\n");

  File root = SD.open("/");      // 루트 파일/디렉터리 열기

  deleteDirectory(root, "/");      // 재귀적 디렉터리 리스팅

  Serial.println("\n* 파일과 디렉터리 삭제를 끝냈습니다.");
}

void deleteDirectory(File dir, String path) {
  while (true) {
    File entry = dir.openNextFile();  // 다음 파일 열기
    if (!entry) {         // 현재 디렉터리 내 파일 리스팅 끝
      break;
    }

    if (entry.isDirectory()) {    // 디렉터리인 경우
      String subDirPath = path + entry.name() + '/';

      deleteDirectory(entry, subDirPath);

      entry.close();
      SD.rmdir(subDirPath);

      Serial.println(String(" => ") + subDirPath);
    }
    else {
      String filePath = path + entry.name();

      entry.close();
      SD.remove(filePath);

      Serial.println(String(" => ") + filePath);
    }
  }
}

void loop() {
}
