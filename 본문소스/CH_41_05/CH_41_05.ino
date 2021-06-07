#include <openGLCD.h>

Image_t icon;         // 표시할 이미지

void setup() {
  GLCD.Init();        // 그래픽 LCD 초기화

  // 사용자가 준비한 이미지를 이미지 변환 프로그램을 통해 logo.h 헤더 파일로
  // 변환한 경우 스케치에서는 미리 준비된 이미지와 같은 방법으로 사용할 수 있다.
  icon = logo;

  GLCD.DrawBitmap(icon, 0, 0);    // 이미지 표시
}

void loop() {
}
