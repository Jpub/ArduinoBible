#include <MCUFRIEND_kbv.h>
#define COLOR_NO    17  // 직선 그리기에 사용하는 색상 수

MCUFRIEND_kbv myTFT;

uint16_t colors[] = {     // 직선 그리기 색상
  TFT_BLACK, TFT_NAVY, TFT_DARKGREEN, TFT_DARKCYAN, TFT_MAROON,
  TFT_PURPLE, TFT_OLIVE, TFT_DARKGREY, TFT_BLUE, TFT_GREEN,
  TFT_CYAN, TFT_RED, TFT_MAGENTA, TFT_YELLOW, TFT_ORANGE,
  TFT_GREENYELLOW, TFT_PINK
};

void setup() {
  uint16_t ID = myTFT.readID();
  myTFT.begin(ID);      // TFT-LCD 초기화
  myTFT.setRotation(1);       // 가로 모드
}

void loop() {
  lineDemo();
  delay(5000);
}

void lineDemo() {
  int x1 = 0, y1 = 0, x2, y2, colorIndex = 0;
  int w = myTFT.width(), h = myTFT.height();

  myTFT.fillScreen(TFT_WHITE);    // 흰색으로 화면 지우기

  y2 = h - 1;
  for (x2 = 0; x2 < w; x2 += 6) {   // 아래쪽 직선 그리기
    myTFT.drawLine(x1, y1, x2, y2, colors[colorIndex]);
    colorIndex = (colorIndex + 1) % COLOR_NO;
  }

  x2 = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) {   // 위쪽 직선 그리기
    myTFT.drawLine(x1, y1, x2, y2, colors[colorIndex]);
    colorIndex = (colorIndex + 1) % COLOR_NO;
  }
}
