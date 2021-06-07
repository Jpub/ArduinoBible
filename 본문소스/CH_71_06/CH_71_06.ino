#include "CircularStringFinder.h"

CircularStringFinder csf(10);    // 객체 생성

String testInput = "...<key><value 1>,...<key><value 2>,...<newKey><value 3>,...";
int foundCount = 0;     // 값 탐색 횟수

void setup() {
  Serial.begin(9600);

  csf.setKey("<key>", ',');     // 시작 문자열과 종료 문자 설정
  int N = testInput.length();

  for (int i = 0; i < N; i++) {   // 테스트 데이터 입력
    byte status = csf.add(testInput[i]);  // 문자 추가 및 검색
    if (status == STATE_VALUE_FOUND) {
      foundCount++;

      Serial.print("* 발견된 값 ");
      Serial.print(foundCount);
      Serial.print(" : \"");
      Serial.print(csf.getValue());
      Serial.println('\"');

      switch (foundCount) {
        case 1:
          csf.restart();      // 같은 설정으로 검색 다시 시작
          break;
        case 2:
          csf.setKey("<newKey>", ',');  // 새로운 설정으로 검색 다시 시작
          break;
        case 3:
          csf.restart();
          break;
      }
    }
  }
}

void loop() {
}
