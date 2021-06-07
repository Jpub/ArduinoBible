#include <TinyWireM.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27      // 텍스트 LCD의 I2C 주소

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2); // (주소, 16문자, 2줄)

void setup() {
  TinyWireM.begin();      // I2C 마스터 라이브러리 초기화

  lcd.init();           // LCD 초기화
  lcd.backlight();

  lcd.print("Hello Text LCD");
  lcd.setCursor(1, 1);
  lcd.print("from ATtiny85");
}

void loop() {
}
