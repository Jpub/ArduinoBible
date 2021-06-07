#include <USBKeyboard.h>

void setup() {
  Keyboard.init();        // 키보드 초기화
}

void loop() {
  Keyboard.print("Hello USB Keyboard");   // 키보드 입력
  Keyboard.sendKeyStroke(KEY_ENTER);

  delay(1000);
}
