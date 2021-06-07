#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);  // RS핀, E핀, 데이터 핀 4개

byte custom_character[4][8] = {
  {0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00}, // heart
  {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00},   // bell
  {0x1F, 0x15, 0x1F, 0x1F, 0x0E, 0x0A, 0x1B, 0x00},   // alien
  {0x00, 0x11, 0x00, 0x00, 0x11, 0x0E, 0x00, 0x00}
};  // smile

void setup() {
  lcd.begin(16, 2);     // LCD 크기 지정, 2줄 16칸

  for (int i = 0; i < 4; i++) {   // 사용자 정의 문자 생성
    lcd.createChar(i, custom_character[i]);
  }

  lcd.clear();          // 화면 지우기
  lcd.print("Custom Character");
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(i * 4, 1);
    lcd.write(i);       // 사용자 정의 문자 표시
  }
}

void loop() {
}
