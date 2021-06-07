#include <openGLCD.h>

Image_t icon;         // 표시할 이미지

void setup() {
  GLCD.Init();        // 그래픽 LCD 초기화

  // 미리 준비된 이미지 중에서 표시할 이미지 선택
  icon = openGLCD128x64;

  GLCD.DrawBitmap(icon, 0, 0);    // 이미지 표시
}

void loop() {
}
