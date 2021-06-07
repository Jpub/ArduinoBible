#include <Adafruit_NeoMatrix.h>
#include <CircularBuffer.h>

#define UP       0   // 이동 방향 상수
#define DOWN    1
#define LEFT    2
#define RIGHT     3
#define NO_MOVE   4   // 이전 이동 방향 유지

// 방향 결정을 위한 가변저항의 값 범위
#define VR_MIN    100   // [0 100] 왼쪽/위쪽
#define VR_MID1   400   // [400 600] 움직임 없음
#define VR_MID2   600
#define VR_MAX  900   // [900 1023] 오른쪽/아래쪽

#define STATE_INITIAL     1   // 초기 상태
#define STATE_MOVING    2   // 게임 진행 상태
#define STATE_GAME_END  3 // 게임 종료 상태

#define GROWING 2       // 사과를 먹었을 때 길어지는 몸 길이
#define INTERVAL 300      // 뱀이 움직이는 시간 간격

int ROWS = 8, COLUMNS = 8;    // 네오픽셀 매트릭스 크기
int PIN = 6;          // 네오픽셀 매트릭스 제어 핀

// 네오픽셀 매트릭스 제어 객체 생성
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

const uint16_t snakeColor1 = matrix.Color(0, 0, 255);   // 뱀 머리 색
const uint16_t snakeColor2 = matrix.Color(0, 100, 0);   // 뱀 몸 색
const uint16_t logoColor = matrix.Color(100, 0, 0);
const uint16_t appleColor = matrix.Color(255, 0, 0);  // 사과 색

byte appleX, appleY;      // 현재 사과 위치
byte isGrowing;         // 사과를 먹어 길어져야 할 남은 길이
byte direction;         // 현재 뱀의 진행 방향
byte state;           // 게임의 상태

// 초기 상태의 뱀 데이터로 (x, y) 좌표 순서이며 뒤쪽이 머리를 나타냄
const byte startSnake[] = { 1, 4, 1, 3, 2, 3 };
const byte halfCircle[]       // 시작 화면 원 그리기 데이터 (x, y)
  = { 3, 0, 2, 0, 1, 1, 0, 2, 0, 3, 0, 4, 0, 5, 1, 6, 2, 7, 3, 7 };
CircularBuffer<byte, 64> buffer;    // 뱀 위치를 최대 64개 저장
unsigned long time_previous;    // 움직임 시간 간격 조절

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(10);     // 밝기 정도 [0 255]

  time_previous = millis();

  state = STATE_INITIAL;    // 초기 상태에서 시작
  startScreen();        // 시작 화면 표시

  randomSeed(analogRead(A5));     // 난수 발생기 초기화
}

void initGameSetting() {
  direction = RIGHT;      // 진행 방향 초기화

  buffer.clear();         // 뱀 위치 버퍼 비움
  // (x, y) 위치를 4비트씩 나누어서 1바이트로 저장
  for (byte i = 0; i < sizeof(startSnake); i += 2) {
    buffer.unshift( (startSnake[i] << 4) | startSnake[i + 1] );
  }

  appleX = 255; appleY = 255;     // 사과 없음
  isGrowing = 0;      // 몸이 길어지지 않는 상태
}

void showSnake() {
  matrix.clear();         // 모든 픽셀 끄기
  byte xy, x, y;
  for (decltype(buffer)::index_t i = 1; i < buffer.size(); i++) {
    xy = buffer[i];
    x = xy >> 4;
    y = xy & 0x0F;
    matrix.drawPixel(x, y, snakeColor2);  // 뱀의 몸 표시
  }
  xy = buffer[0];
  x = xy >> 4;
  y = xy & 0x0F;
  matrix.drawPixel(x, y, snakeColor1);  // 뱀의 머리 표시

  // 사과 표시, (255, 255)인 경우는 사과가 없는 경우임
  matrix.drawPixel(appleX, appleY, appleColor);

  matrix.show();        // 매트릭스로 데이터 전송
}

// 조이스틱 움직임에 따른 회전 방향 결정
// UP, DOWN, LEFT, RIGHT, NO_MOVE 중 하나의 값 반환
byte checkValidRotation() {
  int a1 = analogRead(A0);    // X 축
  int a2 = analogRead(A1);    // Y 축

  // 위아래로 움직이고 있을 때 조이스틱을 왼쪽으로 움직이면 왼쪽 회전
  if (a1 <= VR_MIN && a2 >= VR_MID1 && a2 <= VR_MID2) {
    if (direction == UP || direction == DOWN) return LEFT;
    else return NO_MOVE;
  }
  // 위아래로 움직이고 있을 때 조이스틱을 오른쪽으로 움직이면 오른쪽 회전
  else if (a1 >= VR_MAX && a2 >= VR_MID1 && a2 <= VR_MID2) {
    if (direction == UP || direction == DOWN) return RIGHT;
    else return NO_MOVE;
  }
  // 좌우로 움직이고 있을 때 조이스틱을 위로 움직이면 위쪽 회전
  else if (a2 <= VR_MIN && a1 >= VR_MID1 && a1 <= VR_MID2) {
    if (direction == LEFT || direction == RIGHT) return UP;
    else return NO_MOVE;
  }
  // 좌우로 움직이고 있을 때 조이스틱을 아래로 움직이면 아래쪽 회전
  else if (a2 >= VR_MAX && a1 >= VR_MID1 && a1 <= VR_MID2) {
    if (direction == LEFT || direction == RIGHT) return DOWN;
    else return NO_MOVE;
  }
  else {
    return NO_MOVE;   // 회전할 수 없거나 조이스틱을 움직이지 않았음
  }
}

void updatePosition() {
  byte xy = buffer[0];      // 뱀 머리 위치
  byte headX = xy >> 4, headY = xy & 0x0F;

  // 새로운 머리 위치를 결정하여 추가
  if (direction == UP)    headY--;
  else if (direction == DOWN)   headY++;
  else if (direction == LEFT)   headX--;
  else if (direction == RIGHT)  headX++;
  buffer.unshift( (headX << 4) | headY );

  // 사과를 먹어 몸이 길어지는 상태가 아니면 꼬리를 자르고
  // 몸이 길어지는 상태면 길어질 몸 길이가 0이 될 때까지 감소
  if (isGrowing == 0) buffer.pop();
  else isGrowing--;
}

boolean anyMovement() {     // 조이스틱의 전후좌우 움직임 여부
  int a1 = analogRead(A0);    // X 축
  int a2 = analogRead(A1);    // Y 축

  if (a1 <= VR_MIN || a1 >= VR_MAX || a2 <= VR_MIN || a2 >= VR_MAX)
    return true;
  else
    return false;
}

boolean hitBarrier() {    // 장애물과 충돌, 즉, 화면을 벗어난 경우 검사
  byte xy = buffer[0];
  byte x = xy >> 4, y = xy & 0x0F;

  if (x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) return true;
  else return false;
}

boolean hitApple() {      // 뱀 머리와 사과 충돌 감지
  byte xy = buffer[0];
  byte x = xy >> 4, y = xy & 0x0F;

  if (x == appleX && y == appleY) return true;
  else return false;
}

void makeApple() {      // 새로운 사과 위치 결정
  int x, y;
  do {
    x = random(8);
    y = random(8);
  } while ( isSnakeBody(x, y) );    // 뱀 위치와 겹치는 경우 다시 결정

  appleX = x; appleY = y;   // 새로운 사과 위치
}

boolean isSnakeBody(int _x, int _y) { // 뱀 위치와 겹치는지 검사
  byte xy, x, y;

  for (decltype(buffer)::index_t i = 0; i < buffer.size(); i++) {
    xy = buffer[i];
    x = xy >> 4;
    y = xy & 0x0F;

    if (x == _x && y == _y) return true;
  }

  return false;
}

boolean hitBody() {     // 머리와 몸이 부딪힌 경우 검사
  byte xy = buffer[0];
  byte _x = xy >> 4, _y = xy & 0x0F;
  byte x, y;

  for (decltype(buffer)::index_t i = 1; i < buffer.size(); i++) {
    xy = buffer[i];
    x = xy >> 4;
    y = xy & 0x0F;

    if (x == _x && y == _y) return true;
  }

  return false;
}

void loop() {
  if (state == STATE_INITIAL) {   // 초기 상태
    if (anyMovement()) {      // 조이스틱을 움직이면
      initGameSetting();      // 게임 설정 초기화
      showSnake();      // 뱀 표시
      state = STATE_MOVING;   // 게임 진행 상태로 바꿈
      delay(1000);      // 1초 후 움직이기 시작
    }
  }
  else if (state == STATE_MOVING) { // 게임 진행 상태
    unsigned long time_current = millis();

    // 조이스틱 움직임에 따라 회전 방향 결정
    byte buttonCheck = checkValidRotation();
    if (buttonCheck != NO_MOVE) {
      direction = buttonCheck;
      delay(INTERVAL / 2);    // 연속 회전 방지
    }

    // 몸이 길어지지 않는 상태이고 사과가 없으면 새로운 사과 생성
    if (isGrowing == 0 && appleX == 255) makeApple();

    if (time_current - time_previous >= INTERVAL) {
      time_previous = time_current;

      updatePosition();     // 진행 방향으로 움직임
      if (hitApple()) {       // 사과를 먹은 경우
        isGrowing = GROWING;    // 몸이 길어지도록 표시
        appleX = 255; appleY = 255; // 사과 숨김
      }

      showSnake();      // 뱀 표시

      if (hitBarrier() || hitBody()) {  // 장애물이나 몸 일부와 부딪힌 경우
        endScreen();      // 게임 종료 화면 표시
        state = STATE_GAME_END; // 게임 종료 상태로 바꿈
      }
    }
  }
  else if (state == STATE_GAME_END) { // 게임 종료 상태
    if (anyMovement()) {      // 조이스틱을 움직이면
      state = STATE_INITIAL;    // 초기 상태로 바꿈
      startScreen();      // 초기 화면 표시
      delay(1000);
    }
  }
}

void startScreen() {      // 초기 화면 표시
  matrix.clear();       // 매트릭스 지우기

  for (byte i = 0; i < sizeof(halfCircle); i += 2) {    // 원 표시
    matrix.drawPixel(halfCircle[i], halfCircle[i + 1], logoColor);
    matrix.drawPixel(7 - halfCircle[i], halfCircle[i + 1], logoColor);
  }

  int n = sizeof(startSnake);   // 초기 상태 뱀 표시
  for (byte i = 0; i < n - 2; i += 2) {
    matrix.drawPixel(startSnake[i], startSnake[i + 1], snakeColor2);
  }
  matrix.drawPixel(startSnake[n - 2], startSnake[n - 1], snakeColor1);

  matrix.show();        // 매트릭스로 데이터 전송
}

void endScreen() {      // 게임 종료 화면 표시
  for (byte i = 0; i < 8; i++) {    // ‘X‘자 모양 표시
    matrix.drawPixel(7 - i, i, logoColor);
    matrix.drawPixel(i, i, logoColor);
    matrix.show();
    delay(50);
  }
}
