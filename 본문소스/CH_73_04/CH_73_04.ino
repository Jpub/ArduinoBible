#include <Keyboard.h>

int ON_OFF_BTN = 13;       // 키보드 on/off 버튼

int BUTTON_LEFT = 2;      // 왼쪽 화살표 키
int BUTTON_RIGHT = 3;       // 오른쪽 화살표 키
int BUTTON_UP = 4;      // 위쪽 화살표 키
int BUTTON_DOWN = 5;      // 아래쪽 화살표 키

void setup() {
  Keyboard.begin();       // 키보드 시작

  pinMode(ON_OFF_BTN, INPUT);   // 버튼을 입력으로 설정
  // 화살표 키에 해당하는 버튼은 저항 없이 내장 풀업 저항 사용
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  if (digitalRead(ON_OFF_BTN) == HIGH) {  // 키보드 기능이 켜진 경우에만 키 값 전송
    if (digitalRead(BUTTON_LEFT) == LOW) {
      Keyboard.write(KEY_LEFT_ARROW);
      Serial.println("* 왼쪽 화살표 키 누름");
    }
    if (digitalRead(BUTTON_RIGHT) == LOW) {
      Keyboard.write(KEY_RIGHT_ARROW);
      Serial.println("* 오른쪽 화살표 키 누름");
    }
    if (digitalRead(BUTTON_UP) == LOW) {
      Keyboard.write(KEY_UP_ARROW);
      Serial.println("* 위쪽 화살표 키 누름");
    }
    if (digitalRead(BUTTON_DOWN) == LOW) {
      Keyboard.write(KEY_DOWN_ARROW);
      Serial.println("* 아래쪽 화살표 키 누름");
    }

    delay(100);
  }
}
