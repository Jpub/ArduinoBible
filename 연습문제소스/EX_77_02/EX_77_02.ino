#include <DigiKeyboard.h>

int count = 0;

void setup() {
}

void loop() {
  DigiKeyboard.println(count);    // 키보드 입력
  count++;            // 카운터 증가
  DigiKeyboard.delay(1000);
}
