#include <openGLCD.h>

void setup() {
  GLCD.Init();        // 그래픽 LCD 초기화

  GLCD.DrawLine(0, 0, 127, 63);   // 직선
  GLCD.DrawLine(127, 0, 0, 63);

  for (int r = 30; r >= 5; r -= 5) {
    if (r % 10 == 0) {      // 채워진 원
      GLCD.FillCircle(64, 32, r, PIXEL_ON);
    }
    else {          // 빈 원, 원 내부를 강제로 지움
      GLCD.FillCircle(64, 32, r, PIXEL_OFF);
    }
  }
}

void loop() {
}
