#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // (주소, 열, 행)

byte rowPins[4] = { 9, 8, 7, 6 };     // 행 연결 핀
byte colPins[4] = { 5, 4, 3, 2 };     // 열 연결 핀

const byte ROWS = 4;      // 행 수
const byte COLS = 4;      // 열 수

char key_values[] = {       // 키값
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'
};

byte X = 0, Y = 0;      // 텍스트 LCD에 키 입력을 표시할 위치

// 키패드 객체 생성 (키값, 행 연결 핀, 열 연결 핀, 행 수, 열 수)
Keypad keypad = Keypad( key_values, rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.init();           // LCD 초기화
  lcd.clear();          // LCD 화면 지우기
  lcd.backlight();      // 백라이트 켜기
}

void loop() {
  char key = keypad.getKey();     // 눌러진 키 확인

  if (key) {
    lcd.setCursor(X, Y);      // 현재 출력 위치로 이동
    lcd.write(key);     // 키 값 출력

    // 다음 출력 위치 조정
    X = X + 1;
    if (X == 16) {
      Y = (Y + 1) % 2;
      X = 0;
    }

    lcd.setCursor(X, Y);      // 다음 출력 위치로 이동
    lcd.write(' ');       // 다음 출력 위치의 기존 출력 지우기
  }
}
