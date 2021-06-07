#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // (주소, 열, 행)

void setup() {
  lcd.init();           // LCD 초기화

  lcd.clear();
  lcd.backlight();      // 백라이트 켜기

  lcd.print("Hello, I2C LCD!");   // 문자열 출력
}

void loop() {
}
