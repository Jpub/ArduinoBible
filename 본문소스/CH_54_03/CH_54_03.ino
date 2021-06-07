#include <SD.h>

#define SD_CS 10      // SD 카드 Chip/Slave Select
const char fileName[] = "test.txt";

void setup() {
  Serial.begin(9600);

  Serial.println("* SD 카드를 초기화합니다.");
  if (!SD.begin(SD_CS)) {       // SD 카드 초기화
    Serial.println("** 초기화 과정에서 오류가 발생했습니다.");
    while (1);
  }
  Serial.println("* 초기화를 완료했습니다.");

  if (SD.exists(fileName)) {
    Serial.println("* 기존 파일을 삭제합니다.");
    SD.remove(fileName);
  }

  // 텍스트 파일을 쓰기 모드로 열기
  File myFile = SD.open(fileName, FILE_WRITE);

  if (myFile) {
    Serial.println("* 텍스트 파일로 쓰기를 시작합니다.");

    int count = 0;
    for (int i = 1; i <= 5; i++) {    // 5번 쓰기
      myFile.print("Count : ");
      myFile.println(i);
    }
    myFile.close();     // 파일 닫기
    Serial.println("* 텍스트 파일로 쓰기를 끝냈습니다.");
  }

  myFile = SD.open(fileName);     // 디폴트 모드인 읽기 모드로 열기
  if (myFile) {
    Serial.println("* 텍스트 파일 내용을 읽기 시작합니다.");
    Serial.println();

    while (myFile.available()) {    // 텍스트 파일에서 읽기
      Serial.write(myFile.read());    // 시리얼 모니터로 출력
    }
    myFile.close();       // 텍스트 파일 닫기

    Serial.println();
    Serial.println("* 텍스트 파일 내용 읽기를 끝냈습니다.");
  }
  else {            // 텍스트 파일 열기 실패
    Serial.println("* 텍스트 파일을 여는 과정에서 오류가 발생했습니다.");
  }
}

void loop() {
}
