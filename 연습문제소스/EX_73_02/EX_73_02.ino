#include <Keyboard.h>

int ON_OFF_BTN = 13;
int CTRL_C = 2;
int CTRL_V = 3;

void setup() {
  pinMode(ON_OFF_BTN, INPUT);
  pinMode(CTRL_C, INPUT_PULLUP);
  pinMode(CTRL_V, INPUT_PULLUP);

  Keyboard.begin();

  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  if (digitalRead(ON_OFF_BTN) == HIGH) {
    if (digitalRead(CTRL_C) == LOW) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      Keyboard.releaseAll();
      Serial.println("* \'Ctrl + C\'를 눌러 내용을 복사했습니다.");
      delay(500);
    }
    else if (digitalRead(CTRL_V) == LOW) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      Keyboard.releaseAll();
      Serial.println("* \'Ctrl + V\'를 눌러 내용을 붙여넣었습니다.");
      delay(500);
    }
  }
}
