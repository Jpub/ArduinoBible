#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // (주소, 열, 행)

const byte PROGMEM custom_character[4][8] = {
  {0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00},   // heart
  {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00},   // bell
  {0x1F, 0x15, 0x1F, 0x1F, 0x0E, 0x0A, 0x1B, 0x00},   // alien
  {0x00, 0x11, 0x00, 0x00, 0x11, 0x0E, 0x00, 0x00}
};   // smile

void setup() {
  lcd.init();           // LCD 초기화

  // 플래시 메모리 데이터로 사용자 정의 문자 생성
  for (int i = 0; i < 4; i++) {
    createCharFromFlash(i, custom_character[i]);
  }

  lcd.clear();          // 화면 지우기
  lcd.backlight();      // 백라이트 켜기

  lcd.print("Custom Character");
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(i * 4, 1);
    lcd.write(i);         // 사용자 정의 문자 표시
  }
}

void loop() {
}

// 플래시 메모리 사용
void createCharFromFlash(uint8_t location, const uint8_t charmap[]) {
  location &= 0x7;      // 하위 3비트로 0에서 7까지 구분
  lcd.command(LCD_SETCGRAMADDR | (location << 3));
  for (int i = 0; i < 8; i++) {
    // 플래시 메모리에 있는 문자 데이터로 사용자 정의 문자 생성
    lcd.write(pgm_read_byte(charmap + i));
  }
}
