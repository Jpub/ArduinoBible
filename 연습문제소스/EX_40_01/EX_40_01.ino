#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);  // RS핀, E핀, 데이터 핀 4개

void setup() {
  lcd.begin(16, 2);       // LCD 초기화
  lcd.clear();          // LCD 화면 지우기

  randomSeed(analogRead(A0));
}

void loop() {
  int row = random(0, 2);
  int col = random(0, 17);

  char ch = random(0, 35) + 'A'; // 범위 밖은 공백으로 대체

  if (ch > 'Z') {
    ch = ' ';
  }

  lcd.setCursor(col, row);
  lcd.write(ch);

  delay(200);
}
