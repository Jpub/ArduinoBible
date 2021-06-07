#include <Adafruit_NeoMatrix.h>

#define DOT(block, subPattern, x, y) \
  patterns[patternStart[block] + subPattern][y * 4 + x]

#define FOREGROUND  1     // 블록 패턴에서의 전경과 배경
#define BACKGROUND  0

#define UP      0   // 이동 방향 상수
#define DOWN    1
#define LEFT    2
#define RIGHT     3
#define NO_MOVE   4   // 조이스틱 움직임 없음

// 방향 결정을 위한 가변저항의 값 범위
#define VR_MIN    100   // [0 100] 왼쪽/위쪽
#define VR_MID1   400   // [400 600] 움직임 없음
#define VR_MID2   600
#define VR_MAX  900   // [900 1023] 오른쪽/아래쪽

#define STATE_INITIAL     1   // 초기 상태
#define STATE_GAME_PLAYING  2   // 게임 진행 상태
#define STATE_GAME_END  3   // 게임 종료 상태

const byte patterns[][16] = {   // 블록 데이터
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
byte currentBlock = 0;      // 현재 블록 인덱스
byte currentSubPattern = 0;     // 현재 블록의 회전에 따른 하위 인덱스
int currentX, currentY;       // 블록의 현재 위치

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

byte state = STATE_INITIAL;     // 초기 화면에서 시작

int INTERVAL = 500;       // 블록 움직임 간격
unsigned long timePrevious;     // 블록 움직임 간격
int JOYSTICK_DELAY = 150;     // 조이스틱 연속 조작 간격

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(5);    // 밝기 정도 [0 255]

  randomSeed(analogRead(A3));     // 난수 발생기 초기화

  displayInitialScreen();       // 초기 화면 표시
  timePrevious = millis();
}

void displayGameEndScreen() {   // 게임 종료 화면 표시
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 8; x++) {
      if (gameScreen[y][x] != 0)    // 남은 블록을 흰색으로 모두 바꿈
        matrix.drawPixel(x, y, matrix.Color(0xAA, 0xAA, 0xAA));
    }
    matrix.show();
    delay(100);       // 줄 단위로 순차적으로 진행
  }

  for (int y = 5; y < 13; y++) {    // 화면 가운데 화살표 표시
    int x1 = y - 5;
    int x2 = 12 - y;
    matrix.drawPixel(x1, y, matrix.Color(0xFF, 0x00, 0x00));
    matrix.drawPixel(x2, y, matrix.Color(0xFF, 0x00, 0x00));
  }
  matrix.show();
}

void displayInitialScreen() {   // 초기 화면에 7개 블록 모두 표시
  matrix.clear();
  for (int b = 0; b < 7; b++) {
    int x = (b % 2) * 3;
    int y = (b / 2) * 4 + (b % 2) * 2;
    drawPattern(x, y, b, 0);
  }
  matrix.show();
}

// 게임 화면의 (x, y) 위치부터 시작해서 block번 블록의 subPattern 출력
void drawPattern(byte x, byte y, byte block, byte subPattern) {
  for (byte yy = 0; yy < 4; yy++) {
    for (byte xx = 0; xx < 4; xx++) {
      byte b = DOT(block, subPattern, xx, yy);
      if (b == FOREGROUND) {
        matrix.drawPixel(x + xx, y + yy, colors[block]);
      }
    }
  }
}

int checkMovement() {     // 조이스틱 움직임 검사
  int a1 = analogRead(A0);    // X 축
  int a2 = analogRead(A1);    // Y 축

  if (a1 <= VR_MIN && a2 >= VR_MID1 && a2 <= VR_MID2)   return LEFT;
  if (a1 >= VR_MAX && a2 >= VR_MID1 && a2 <= VR_MID2) return RIGHT;
  if (a2 <= VR_MIN && a1 >= VR_MID1 && a1 <= VR_MID2)   return UP;
  if (a2 >= VR_MAX && a1 >= VR_MID1 && a1 <= VR_MID2)   return DOWN;
  return NO_MOVE;
}

void initializeGameScreen() {   // 게임 화면의 모든 블록 지움
  for (byte y = 0; y < 16; y++)
    for (byte x = 0; x < 8; x++)
      gameScreen[y][x] = 0;
}

void selectCurrentBlock() {   // 난수 함수로 블록 선택
  currentBlock = random(BLOCKS);  // 현재 블록 인덱스
  currentSubPattern = 0;      // 기본 회전 위치에서 시작
  currentX = 1;
  currentY = -2;        // 보이지 않는 위치부터 내려오기 시작
}

void displayGameScreen() {
  matrix.clear();

  for (byte y = 0; y < 16; y++) {     // 게임 화면에 저장된 데이터 표시
    for (byte x = 0; x < 8; x++) {
      int colorIndex = gameScreen[y][x] - 1;
      if (colorIndex != -1) matrix.drawPixel(x, y, colors[colorIndex]);
    }
  }

  int tempX, tempY;
  for (byte y = 0; y < 4; y++) {    // 현재 움직이는 블록 표시
    tempY = currentY + y;
    for (byte x = 0; x < 4; x++) {
      byte b = DOT(currentBlock, currentSubPattern, x, y);
      if (b == FOREGROUND) {
        tempX = currentX + x;
        matrix.drawPixel(tempX, tempY, colors[currentBlock]);
      }
    }
  }

  matrix.show();
}

boolean endOfGame() {     // 게임 종료 검사
  boolean eog = false;

  for (byte x = 0; x < 8; x++) {
    if (gameScreen[0][x] != 0) return true;
  }
  return false;
}

void updateGameScreen() {
  int tempX, tempY;

  for (byte y = 0; y < 4; y++) {    // 현재 블록을 게임 화면에 추가
    tempY = currentY + y;
    if (tempY < 0) continue;
    for (byte x = 0; x < 4; x++) {
      byte b = DOT(currentBlock, currentSubPattern, x, y);
      if (b == FOREGROUND) {
        tempX = currentX + x;
        gameScreen[tempY][tempX] = currentBlock + 1;
      }
    }
  }

  boolean remove;
  for (int y = 15; y >= 0; y--) {   // 줄 제거 여부 판단 및 제거
    remove = true;
    for (int x = 0; x < 8; x++) {
      if (gameScreen[y][x] == 0) {
        remove = false;
        break;
      }
    }
    if (remove) {       // 줄을 지워야 하는 경우
      for (int yy = y; yy > 0; yy--) {  // 줄을 지우고 한 줄씩 내림
        for (int xx = 0; xx < 8; xx++) {
          gameScreen[yy][xx] = gameScreen[yy - 1][xx];
        }
      }
      for (int xx = 0; xx < 8; xx++)  // 첫 번째 줄은 빈칸으로 채움
        gameScreen[0][xx] = 0;
      y++;          // 지우고 내려온 줄을 다시 검사
    }
  }
}

// 지정한 위치에 지정한 블록을 놓았을 때 완전히 보이는 지 검사
boolean fullyShownBlock(int startX, int startY, int subPattern) {
  int tempX, tempY;

  for (int yy = 0; yy < 4; yy++) {
    tempY = startY + yy;
    for (int xx = 0; xx < 4; xx++) {
      byte b = DOT(currentBlock, subPattern, xx, yy);
      if (b == FOREGROUND) {
        tempX = startX + xx;
        if (tempX < 0 || tempX >= 8 || tempY < 0 || tempY >= 16)
          return false;
      }
    }
  }
  return true;
}

// 지정한 위치에 지정한 블록을 놓았을 때 다른 블록과 겹치지 않는 지 검사
boolean placeableOnGameScreen(int startX, int startY, int subPattern) {
  int tempX, tempY;

  for (int yy = 0; yy < 4; yy++) {
    tempY = startY + yy;
    for (int xx = 0; xx < 4; xx++) {
      byte b = DOT(currentBlock, subPattern, xx, yy);
      if (b == FOREGROUND) {
        tempX = startX + xx;
        if (gameScreen[tempY][tempX] != 0) return false;
      }
    }
  }
  return true;
}

boolean possibleMoveLeft() {    // 왼쪽으로 이동 가능 검사
  int nextX = currentX - 1, nextY = currentY;

  if (fullyShownBlock(currentX, currentY, currentSubPattern)
      && fullyShownBlock(nextX, nextY, currentSubPattern)
      && placeableOnGameScreen(nextX, nextY, currentSubPattern))
    return true;
  else return false;
}

boolean possibleMoveRight() {   // 오른쪽으로 이동 가능 검사
  int nextX = currentX + 1, nextY = currentY;

  if (fullyShownBlock(currentX, currentY, currentSubPattern)
      && fullyShownBlock(nextX, nextY, currentSubPattern)
      && placeableOnGameScreen(nextX, nextY, currentSubPattern))
    return true;
  else return false;
}

boolean possibleRotate() {    // 회전 가능 검사
  int nextSubPattern = (currentSubPattern + 1) % patternNo[currentBlock];
  int tempX, tempY;

  if (fullyShownBlock(currentX, currentY, currentSubPattern)
      && fullyShownBlock(currentX, currentY, nextSubPattern)
      && placeableOnGameScreen(currentX, currentY, nextSubPattern))
    return true;
  else return false;
}

boolean possibleMoveDown() {    // 아래쪽으로 이동 가능 검사
  int nextX = currentX, nextY = currentY + 1;
  int tempX, tempY;

  for (byte y = 0; y < 4; y++) {
    tempY = nextY + y;
    if (tempY < 0) continue;    // 일부만 보이는 경우
    for (byte x = 0; x < 4; x++) {
      byte b = DOT(currentBlock, currentSubPattern, x, y);
      if (b == FOREGROUND) {
        tempX = nextX + x;
        if (tempY >= 16 || gameScreen[tempY][tempX] != 0) return false;
      }
    }
  }
  return true;
}

void loop() {
  if (state == STATE_INITIAL) {   // 초기 상태
    if (checkMovement() != NO_MOVE) { // 조이스틱 움직임
      state = STATE_GAME_PLAYING; // 게임 진행 상태로 전환
      initializeGameScreen();   // 게임 화면 초기화
      selectCurrentBlock();   // 난수 함수로 블록 선택
      matrix.clear();     // 네오픽셀 매트릭스 초기화
    }
  }
  else if (state == STATE_GAME_PLAYING) {   // 게임 진행 상태
    byte joystickMove = checkMovement();
    if (joystickMove == LEFT) {     // 조이스틱을 왼쪽으로 움직인 경우
      if (possibleMoveLeft()) {     // 블록을 왼쪽으로 움직일 수 있는 경우
        currentX--;     // 블록 위치 조정
        displayGameScreen();    // 게임 화면 표시
        delay(JOYSTICK_DELAY);    // 조이스틱 움직임 사이 시간 지연
      }
    }
    else if (joystickMove == RIGHT) {   // 조이스틱을 오른쪽으로 움직인 경우
      if (possibleMoveRight()) {
        currentX++;
        displayGameScreen();
        delay(JOYSTICK_DELAY);
      }
    }
    else if (joystickMove == UP) {    // 조이스틱을 위로 움직인 경우
      if (possibleRotate()) {
        currentSubPattern = (currentSubPattern + 1) % patternNo[currentBlock];
        displayGameScreen();
        delay(JOYSTICK_DELAY);
      }
    }
    else if (joystickMove == DOWN) {  // 조이스틱을 아래로 움직인 경우
      if (possibleMoveDown()) {
        currentY++;
        displayGameScreen();
        delay(JOYSTICK_DELAY);
      }
    }

    unsigned long timeCurrent = millis();
    if (timeCurrent - timePrevious >= INTERVAL) { // 블록을 움직일 시간
      timePrevious = timeCurrent;

      if (!possibleMoveDown()) {    // 아래로 움직일 수 없으면
        updateGameScreen();     // 현재 블록을 고정시켜 게임 화면 갱신

        if (endOfGame()) state = STATE_GAME_END;
        else selectCurrentBlock();
      }
      else {          // 블록을 아래로 움직일 수 있으면
        currentY++;       // 블록을 아래로 이동
      }

      if (state == STATE_GAME_END) displayGameEndScreen();
      else displayGameScreen();     // 게임 화면 표시
    }
  }
  else if (state == STATE_GAME_END) { // 게임 종료 상태
    if (checkMovement() != NO_MOVE) { // 조이스틱 움직임
      state = STATE_INITIAL;    // 초기 상태로 전환
      displayInitialScreen();   // 초기 화면 표시
      delay(1000);      // 초기 화면 표시 후 바로 게임 시작 방지
    }
  }
}
