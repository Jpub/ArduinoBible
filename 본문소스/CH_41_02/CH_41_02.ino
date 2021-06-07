#include <openGLCD.h>

void setup() {
  GLCD.Init();        // 그래픽 LCD 초기화

  GLCD.SelectFont(System5x7);   // 출력 폰트 선택

  for (int i = 0; i < 8; i++) { // 문자 단위의 커서 이동
    GLCD.CursorTo(i, i);
    GLCD.print(i);
  }

  for (int i = 0; i < 6; i++) { // 픽셀 단위의 커서 이동
    GLCD.CursorToXY(100, i * 10);
    GLCD.print(char('A' + i));
  }
}

void loop() {
}
