#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 myTFT = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 3900

#define STMPE_CS 8

Adafruit_STMPE610 myTouch = Adafruit_STMPE610(STMPE_CS);

uint16_t colors[] = {
  ILI9341_RED, ILI9341_YELLOW, ILI9341_GREEN,
  ILI9341_CYAN, ILI9341_BLUE, ILI9341_MAGENTA
};
byte previousColor, currentColor;

int16_t BOXSIZE;
int16_t PENRADIUS = 3;

void setup() {
  myTFT.begin();
  myTouch.begin();

  myTFT.setRotation(1);

  BOXSIZE = myTFT.width() / 6;
  myTFT.fillScreen(ILI9341_BLACK);

  for (byte i = 0; i < 6; i++) {
    myTFT.fillRect(BOXSIZE * i, 0, BOXSIZE, BOXSIZE, colors[i]);
  }

  currentColor = 0;
  myTFT.drawRect(BOXSIZE * currentColor, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
}

void loop() {
  if (myTouch.bufferEmpty()) {
    return;
  }

  uint16_t xpos, ypos;

  TS_Point tp = myTouch.getPoint();
  xpos = map(tp.y, TS_MINY, TS_MAXY, 0, myTFT.width());
  ypos = map(tp.x, TS_MAXX, TS_MINX, 0, myTFT.height());

  // 색상 선택 영역
  if (ypos < BOXSIZE) {
    previousColor = currentColor;

    currentColor = xpos / BOXSIZE;
    myTFT.drawRect(currentColor * BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);

    if (previousColor != currentColor) {
      myTFT.fillRect(previousColor * BOXSIZE, 0, BOXSIZE, BOXSIZE, colors[previousColor]);
    }
  }

  // 그리기 영역
  if ( (ypos - PENRADIUS) > BOXSIZE && (ypos + PENRADIUS) < myTFT.height() ) {
    myTFT.fillCircle(xpos, ypos, PENRADIUS, colors[currentColor]);
  }

  // 화면 지우기 영역
  if (ypos > myTFT.height() - 10) {
    myTFT.fillRect(0, BOXSIZE, myTFT.width(), myTFT.height() - BOXSIZE, ILI9341_BLACK);
  }
}
