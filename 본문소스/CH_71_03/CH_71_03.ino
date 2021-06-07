#include "CircularStringFinder.h"

CircularStringFinder csf(10);    // 객체 생성

void setup() {
  Serial.begin(9600);

  csf.printInfo();        // 초기 상태

  for (int i = 0; i < 9; i++) {   // 9개 문자 추가, 버퍼 꽉 참
    csf.addCharacter('A' + i);
  }
  csf.printInfo();

  csf.addCharacter('A' + 9);    // 10번째 문자 추가, 버퍼 넘침
  csf.printInfo();
}

void loop() {
}
