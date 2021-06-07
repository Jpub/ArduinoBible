#include <Mouse.h>

int ON_OFF_BTN = 13;       // 마우스 on/off 버튼
int state = 0;        // 사각형을 그리는 상태
int SIZE = 50;        // 사각형 크기
int MOVE = 20;        // 사각형 이동

void setup() {
  pinMode(ON_OFF_BTN, INPUT);   // 버튼을 입력으로 설정
  Mouse.begin();      // 키보드 동작 시작
}

void loop() {
  // 마우스 기능이 켜진 경우에만 마우스 이벤트 전송
  if (digitalRead(ON_OFF_BTN) == HIGH) {
    switch (state) {
      case 0:         // 시작 위치에서 마우스 왼쪽 버튼 누름
        Mouse.press();
        state = 1;
        break;
      case 1:
        Mouse.move(SIZE, 0, 0);     // (SIZE, 0) 움직임, 오른쪽
        state = 2;
        break;
      case 2:
        Mouse.move(0, SIZE, 0);     // (0, SIZE) 움직임, 아래쪽
        state = 3;
        break;
      case 3:
        Mouse.move(-SIZE, 0, 0);    // (-SIZE, 0) 움직임, 왼쪽
        state = 4;
        break;
      case 4:
        Mouse.move(0, -SIZE, 0);    // (0, -SIZE) 움직임, 위쪽
        Mouse.release();      // 왼쪽 버튼 뗌
        Mouse.move(MOVE, MOVE);   // 다음 사각형 그릴 위치로 이동
        state = 0;
    }
  }
  delay(500);
}
