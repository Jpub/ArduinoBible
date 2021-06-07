#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);   // RS핀, E핀, 데이터 핀 4개

void setup() {
  lcd.begin(20, 4);     // LCD 크기 지정, 4줄 20칸
  lcd.clear();        // LCD 지우기

  for (int i = 'a'; i <= 'z'; i++) {    // 0행과 2행 출력
    lcd.write(i);
  }
  for (int i = 0; i <= 16; i++) {   // 40개 문자 채우기 위한 공백 16개
    lcd.write(' ');
  }

  for (int i = 'A'; i <= 'Z'; i++) {    // 1행과 3행 출력
    lcd.write(i);
  }
}

void loop() {
}
