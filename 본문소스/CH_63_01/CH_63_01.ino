#include <Adafruit_NeoMatrix.h>

#define DOT(block, subPattern, x, y) \
  patterns[patternStart[block] + subPattern][y * 4 + x]

#define POSITION_X  1     // 블록의 x축 표시 시작 위치

#define FOREGROUND  1     // 블록 패턴에서의 전경과 배경
#define BACKGROUND  0

const byte patterns[][16] = {
  {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},   // P0 : 0
  {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},   // P1 : 1
  {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},   // P2 : 3
  {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},   // P3 : 5
  {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0},   // P4 : 7
  {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},   // P5 : 11
  {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},   // P6 : 15
  {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}
};

byte BLOCKS = 7;      // 블록의 종류
// 배열에서 블록 데이터가 시작하는 위치
byte patternStart[7] = {0, 1, 3, 5, 7, 11, 15};
// 각 블록이 회전에 따라 가지는 모양 개수
byte patternNo[7] = {1, 2, 2, 2, 4, 4, 4};

byte gameScreen[16][8] = {0, };     // 게임 화면 저장 배열

int ROWS = 8, COLUMNS = 8;    // 네오픽셀 매트릭스 크기
int NUM_X = 1, NUM_Y = 2;     // x 및 y 방향으로 연결된 매트릭스 수
int PIN = 6;          // 네오픽셀 매트릭스 연결 핀

// 두 개의 연결된 네오픽셀 매트릭스 제어 객체 생성
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS,
                            NUM_X, NUM_Y, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT
                            + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG
                            + NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_COLUMNS);

uint16_t colors[8] = {      // 각 블록의 색상
  matrix.Color(0xFF, 0xD7, 0x00), matrix.Color(0x00, 0xFF, 0xFF),
  matrix.Color(0X00, 0xFF, 0x00), matrix.Color(0xFF, 0x00, 0x00),
  matrix.Color(0xCD, 0x85, 0x3F), matrix.Color(0x00, 0x00, 0xFF),
  matrix.Color(0x8A, 0x2B, 0xE2)
};

unsigned long timePrevious;
int INTERVAL = 500;       // 블록 움직임 간격

int lineStart = 0;      // 28줄(4줄 * 7개 블록) 중 16줄만 표시
// 7개 블록이 현재 게임 화면에 표시되는 서브 패턴
int currentSubPattern[7] = { 0, 1, 0, 1, 0, 1, 0 };

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(5);    // 밝기 정도 [0 255]

  timePrevious = millis();
}

void loop() {
  unsigned long timeCurrent = millis();

  if (timeCurrent - timePrevious >= INTERVAL) {
    timePrevious = timeCurrent;

    showBlocks();     // 현재 블록 표시
    updateSubPatterns();      // 각 블록의 회전 상태 변경
  }
}

void showBlocks() {     // 블록 표시 화면
  // lineStart = (lineStart + 1) % 28;  // 블록이 위로 움직이는 경우
  lineStart = (lineStart - 1 + 28) % 28;  // 블록이 아래로 움직이는 경우
  int lineEnd = lineStart + 16;

  matrix.clear();
  for (int i = lineStart; i < lineEnd; i++) {
    int y = i % 28;
    int blockNo = y / 4;
    int blockY = y % 4;

    for (int j = POSITION_X; j < POSITION_X + 4; j++) {
      int x = j - POSITION_X;
      int subPattern = currentSubPattern[blockNo];
      int pixel = DOT(blockNo, subPattern, x, blockY);
      if (pixel == FOREGROUND) {
        matrix.drawPixel(j, i - lineStart, colors[blockNo]);
      }
    }
  }
  matrix.show();
}

void updateSubPatterns() {
  for (int i = 0; i < 7; i++) {
    currentSubPattern[i] = (currentSubPattern[i] + 1) % patternNo[i];
  }
}
