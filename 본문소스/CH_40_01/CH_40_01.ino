#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);   // RS핀, E핀, 데이터 핀 4개

void setup() {
  lcd.begin(16, 2);       // LCD 크기 지정, 2줄 16칸
  lcd.clear();        // LCD 지우기
  lcd.print("Hello LCD!");      // 문자열 출력
}

void loop() {
}
