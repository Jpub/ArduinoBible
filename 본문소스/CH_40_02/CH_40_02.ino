#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);   // RS핀, E핀, 데이터 핀 4개

void setup() {
  lcd.begin(16, 2);       // LCD 크기 지정, 2줄 16칸
  lcd.clear();        // LCD 지우기

  // 첫 번째 줄에 40개 문자 출력
  for (int i = 0; i < 16; i++) {    // 화면에 나타나는 알파벳 소문자 16개
    lcd.write('a' + i);
  }
  for (int i = 0; i < 24; i++) {    // 숨겨진 24개 공백 문자
    lcd.write(' ');
  }

  // 두 번째 줄에 40개 문자 출력
  for (int i = 0; i < 16; i++) {    // 화면에 나타나는 알파벳 대문자 16개
    lcd.write('A' + i);
  }
  for (int i = 0; i < 24; i++) {    // 숨겨진 24개 공백 문자
    lcd.write(' ');
  }

  lcd.print("@.@");     // 처음부터 다시 시작
}

void loop() {
}
