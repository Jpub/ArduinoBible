#include <Adafruit_NeoMatrix.h>

#define UP       0
#define DOWN    1
#define LEFT    2
#define RIGHT     3

#define INTERVAL  200   // 픽셀을 움직이는 시간 간격

int ROWS = 8, COLUMNS = 8;    // 네오픽셀 매트릭스 크기
int PIN = 6;          // 네오픽셀 매트릭스 연결 핀

// 네오픽셀 매트릭스 제어 객체 생성
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

const uint16_t snakeColor = matrix.Color(0, 0, 255);

byte X, Y;          // 현재 뱀의 머리 위치
byte direction;       // 현재 뱀의 진행 방향

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(20);     // 밝기 정도 [0 255]

  randomSeed(analogRead(A0));   // 난수 생성기 초기화

  X = 1;              // 시작 위치 초기화
  Y = 3;
  direction = RIGHT;      // 진행 방향 초기화
}

void showSnake() {
  matrix.clear();       // 모든 픽셀 끄기
  matrix.drawPixel(X, Y, snakeColor); // 머리 표시
  matrix.show();        // 매트릭스로 데이터 전송
}

void updatePosition() {     // 진행 방향에 따라 머리 위치 갱신
  if (direction == UP)    Y--;
  else if (direction == DOWN)   Y++;
  else if (direction == LEFT)   X--;
  else if (direction == RIGHT)  X++;
}

void decideNextPosition() {   // 다음 이동 위치를 랜덤하게 결정
  int nextX = X, nextY = Y;   // 현재 이동 방향으로 움직일 때 다음 위치
  if (direction == UP)    nextY--;
  else if (direction == DOWN)   nextY++;
  else if (direction == LEFT)   nextX--;
  else if (direction == RIGHT)  nextX++;

  // 다음 위치가 범위를 벗어난 위치거나 랜덤으로 방향을 바꾸도록 선택된 경우
  if (!validMove(nextX, nextY) || timeToChangeDirection()) {
    direction = changeDirectionRandom();  // 방향 전환
  }
  updatePosition();     // 다음 진행 방향에 따라 머리 위치 갱신
}

boolean timeToChangeDirection() {
  byte randomNumber = random(4);  // [0 4), 25% 확률로 방향 전환 결정
  if (randomNumber == 0) return true;
  else return false;
}

boolean validMove(int x, int y) {   // 머리 위치가 유효한 범위인지 확인
  if (x < 0 || x > COLUMNS - 1 || y < 0 || y > ROWS - 1)
    return false;
  else  return true;
}

// 회전할 수 있는 방향 중 실제 회전 방향을 랜덤하게 결정
byte changeDirectionRandom() {
  // 위아래로 움직이는 경우 좌우로만 방향을 바꿀 수 있음
  if (direction == UP || direction == DOWN) {
    boolean check1 = validMove(X - 1, Y);
    boolean check2 = validMove(X + 1, Y);

    if (check1) {       // 왼쪽으로 회전 가능
      if (check2) {       // 왼쪽 및 오른쪽으로 회전 가능
        byte rn = random(2);    // 0 or 1
        if (rn == 0)  return LEFT;
        else    return RIGHT;
      }
      else {          // 왼쪽만 회전 가능
        return LEFT;
      }
    }
    else {          // 왼쪽으로 회전 불가능
      return RIGHT;
    }
  }
  // 좌우로 움직이는 경우 위아래로만 방향을 바꿀 수 있음
  else {
    boolean check1 = validMove(X, Y - 1);
    boolean check2 = validMove(X, Y + 1);

    if (check1) {       // 위쪽으로 회전 가능
      if (check2) {       // 위쪽 및 아래쪽으로 회전 가능
        byte rn = random(2);    // 0 or 1
        if (rn == 0)  return UP;
        else    return DOWN;
      }
      else {          // 위쪽으로만 회전 가능
        return UP;
      }
    }
    else {          // 위쪽으로 회전 불가능
      return DOWN;
    }
  }
}

void loop() {
  showSnake();        // 뱀 머리 표시
  decideNextPosition();     // 다음 이동 위치 결정
  delay(INTERVAL);
}
