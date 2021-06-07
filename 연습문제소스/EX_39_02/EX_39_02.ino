#include <LedControl.h>

LedControl matrix = LedControl(12, 11, 10, 1); // 객체 생성

byte no[][8] = {
  { B00000000, B01111110, B10000001, B10000001, B10000001, B10000001, B01111110, B00000000 },
  { B00000000, B00000000, B00000000, B01000000, B11111111, B00000000, B00000000, B00000000 },
  { B00000000, B01000001, B10000011, B10000101, B10001001, B10010001, B01100001, B00000000 },
  { B00000000, B01000010, B10000001, B10010001, B10010001, B10010001, B01101110, B00000000 },
  { B00000000, B00011000, B00101000, B01001000, B10001000, B11111111, B00001000, B00000000 },
  { B00000000, B11110001, B10010001, B10010001, B10010001, B10010001, B10001110, B00000000 },
  { B00000000, B01111110, B10010001, B10010001, B10010001, B10010001, B01001110, B00000000 },
  { B00000000, B10000001, B10000010, B10000100, B10001000, B10010000, B11100000, B00000000 },
  { B00000000, B01101110, B10010001, B10010001, B10010001, B10010001, B01101110, B00000000 },
  { B00000000, B01100000, B10010001, B10010010, B10010100, B10011000, B01100000, B00000000 }
};

unsigned long time_previous;
int INTERVAL = 1000;

int index = 0;

void setup() {
  matrix.shutdown(0, false); // 정상 동작 모드
  matrix.setIntensity(0, 5); // 밝기 설정
  matrix.clearDisplay(0); // LED 매트릭스 끄기

  time_previous = millis();
  showNumber();
}

void showNumber() {
  for (int col = 0; col < 8; col++) {
    matrix.setColumn(0, col, no[index][col]);
  }
}

void loop() {
  unsigned long time_current = millis();

  if (time_current - time_previous >= INTERVAL) {
    time_previous = time_current;

    index = (index + 1) % 10;

    showNumber();
  }
}
