#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

#define MINPRESSURE     200 // 터치패널을 눌렀을 때 최소 입력
#define MAXPRESSURE     1000  // 터치패널을 눌렀을 때 최대 입력

MCUFRIEND_kbv myTFT;

const int XP = 6, XM = A2, YP = A1, YM = 7; // 터치패널 사용 핀
const int TS_LEFT = 907, TS_RIGHT = 136;  // 터치패널 입력 범위
const int  TS_TOP = 942, TS_BOTTOM = 139;

uint16_t colors[] = {
  TFT_RED, TFT_YELLOW, TFT_GREEN,
  TFT_CYAN, TFT_BLUE, TFT_MAGENTA
};
byte previousColor, currentColor;   // 색상 인덱스

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;         // 터치 정보

int16_t BOXSIZE;      // 색상 선택 영역의 크기
int16_t PENRADIUS = 1;

void setup() {
  uint16_t ID = myTFT.readID();
  myTFT.begin(ID);
  myTFT.setRotation(1);     // landscape(가로) 모드

  BOXSIZE = myTFT.width() / 6;
  myTFT.fillScreen(TFT_BLACK);  // 화면 지우기

  for (byte i = 0; i < 6; i++) {    // 색상 선택 상자 그리기
    myTFT.fillRect(BOXSIZE * i, 0, BOXSIZE, BOXSIZE, colors[i]);
  }

  currentColor = 0;
  // 선택된 색상에 흰색 테두리 표시 (x, y, width, height, color)
  myTFT.drawRect(
    BOXSIZE * currentColor, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
}

void loop() {
  uint16_t xpos, ypos;      // 화면 좌표
  tp = ts.getPoint();     // 터치 정보 얻기

  // 터치 입력 후 TFT-LCD와 함께 사용하는 핀을 출력으로 되돌림
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    // setRotation(0) : portrait(세로) 모드
    // xpos = map(tp.x, TS_LEFT, TS_RIGHT, 0, myTFT.width());
    // ypos = map(tp.y, TS_TOP, TS_BOTTOM, 0, myTFT.height());

    // setRotation(1) : landscape(가로) 모드
    xpos = map(tp.y, TS_TOP, TS_BOTTOM, 0, myTFT.width());
    ypos = map(tp.x, TS_RIGHT, TS_LEFT, 0, myTFT.height());

    if (ypos < BOXSIZE) {     // 색상 선택 영역을 터치한 경우
      previousColor = currentColor;

      currentColor = xpos / BOXSIZE;
      if (previousColor != currentColor) {  // 색상 선택 박스 다시 그리기
        myTFT.drawRect(     // 현재 선택 박스 그리기
          currentColor * BOXSIZE, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        myTFT.fillRect(previousColor * BOXSIZE,  // 이전 선택 박스 지우기
                       0, BOXSIZE, BOXSIZE, colors[previousColor]);
      }
    }

    // 그리기 영역을 터치한 경우
    if ( (ypos - PENRADIUS) > BOXSIZE
         && (ypos + PENRADIUS) < myTFT.height() ) {
      myTFT.fillCircle(xpos, ypos, PENRADIUS, colors[currentColor]);
    }

    // 화면 지우기 영역을 터치한 경우
    if (ypos > myTFT.height() - 10) {
      myTFT.fillRect(0, BOXSIZE,  // 화면 지우기
                     myTFT.width(), myTFT.height() - BOXSIZE, TFT_BLACK);
    }
  }
}
