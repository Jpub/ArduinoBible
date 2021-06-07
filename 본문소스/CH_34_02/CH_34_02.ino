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
  char key = keypad.getKey();   // 눌러진 키 확인

  if (key) {
    Serial.println(String('\'') + key + "\' 키를 눌렀습니다.");
  }
}
