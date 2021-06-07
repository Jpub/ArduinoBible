#include <Keypad.h>

byte rowPins[4] = { 9, 8, 7, 6 };     // 행 연결 핀
byte colPins[4] = { 5, 4, 3, 2 };     // 열 연결 핀

const byte ROWS = 4;      // 행 수
const byte COLS = 4;      // 열 수

char key_values[] = {     // 키값
  '1', '2', '3', 'A', '4', '5', '6', 'B',
  '7', '8', '9', 'C', '*', '0', '#', 'D'
};

// 키패드 객체 생성 (키값, 행 연결 핀, 열 연결 핀, 행 수, 열 수)
Keypad keypad = Keypad( key_values, rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (keypad.getKeys()) {     // 상태가 변한 키 확인
    for (int i = 0; i < LIST_MAX; i++) {  // 최대 10개까지 관리
      if ( keypad.key[i].stateChanged ) { // 상태 변화 여부
        String msg;
        switch (keypad.key[i].kstate) { // 변한 상태
          case PRESSED:
            msg = "PRESSED";
            break;
          case HOLD:
            msg = "HOLD";
            break;
          case RELEASED:
            msg = "RELEASED";
            break;
          case IDLE:
            msg = "IDLE";
        }

        Serial.print(String("버튼 \'") + keypad.key[i].kchar);
        Serial.print(String("\', ") + keypad.key[i].kcode + "번 버튼의 상태가 ");
        Serial.println(msg + "로 바꼈습니다.");
      }
    }
  }
}
