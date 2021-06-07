#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);   // RS핀, E핀, 데이터 핀 4개
int index = 0;

void setup() {
  lcd.begin(16, 2);     // LCD 크기 지정, 2줄 16칸
}

void loop() {
  lcd.clear();          // 화면 지움
  for (int i = 0; i < 16; i++) {    // 첫 번째 행
    lcd.write(index * 32 + i);
  }
  lcd.setCursor(0, 1);
  for (int i = 16; i < 32; i++) {   // 두 번째 행
    lcd.write(index * 32 + i);
  }

  delay(2000);        // 2초 간격 페이지 전환

  index = (index + 1) % 8;    // 페이지당 32문자, 8페이지 반복
}
