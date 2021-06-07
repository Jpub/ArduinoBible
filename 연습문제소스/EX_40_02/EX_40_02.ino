#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.print("R : ");
}

void loop() {
  int val = analogRead(A0);

  lcd.setCursor(4, 0);
  String s = String(val);

  for (int i = 0; i < 4 - s.length(); i++) {
    lcd.print(' ');
  }
  lcd.print(val);

  delay(500);
}
