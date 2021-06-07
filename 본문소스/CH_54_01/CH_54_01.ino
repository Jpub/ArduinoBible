#include <SD.h>
#define SD_CS 10      // SD 카드 Chip/Slave Select

File root;

void setup() {
  Serial.begin(9600);

  Serial.println("* SD 카드를 초기화합니다.");
  if (!SD.begin(SD_CS)) {     // SD 카드 초기화
    Serial.println("** 초기화 과정에서 오류가 발생했습니다.");
    while (1);
  }
  Serial.println("* 초기화를 완료했습니다.");
  Serial.println("* 디렉터리 리스팅을 시작합니다.\n");

  root = SD.open("/");      // 루트 파일/디렉터리 열기
  printDirectory(root, 0);      // 재귀적 디렉터리 리스팅
  root.close();

  Serial.println("\n* 디렉터리 리스팅을 끝냈습니다.");
}

void printDirectory(File dir, int level) {
  while (true) {
    File entry = dir.openNextFile();  // 다음 파일 열기
    if (!entry) {         // 현재 디렉터리 내 파일 리스팅 끝
      break;
    }

    // 디렉터리 수준(level)에 따라 탭 수를 늘려 맞춤
    for (uint8_t i = 0; i < level; i++) {
      Serial.print(" ");      // 한 수준당 탭 하나 추가
    }

    Serial.print(entry.name());     // 파일 이름 출력

    if (entry.isDirectory()) {    // 디렉터리인 경우
      Serial.println("/");      // 디렉터리 표시로 ‘/’ 출력
      printDirectory(entry, level + 1);   // 서브 디렉터리에 대한 재귀 호출
    }
    else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);  // 파일 크기 출력
    }
    entry.close();        // 리스팅이 끝난 파일 닫기
  }
}

void loop() {
}
