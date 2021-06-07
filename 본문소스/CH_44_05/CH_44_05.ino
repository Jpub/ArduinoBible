#include <Adafruit_ILI9341.h>

#define TFT_DC    9   // TFT-LCD의 DC 핀
#define TFT_CS    10    // TFT-LCD의 CS 핀

// TFT-LCD 제어 객체 생성
Adafruit_ILI9341 myTFT = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  myTFT.begin();      // TFT-LCD 초기화

  myTFT.setRotation(1);       // 가로(landscape) 방향

  myTFT.fillScreen(ILI9341_WHITE);  // 화면 지우기

  myTFT.setTextColor(ILI9341_RED);
  myTFT.setTextSize(2);
  myTFT.println("Adafruit_ILI9341 class inherits from Adafruit_SPITFT class");

  myTFT.setTextColor(ILI9341_BLUE);
  myTFT.println("Adafruit_SPITFT class inherits from Adafruit_GFX class");
}

void loop() {
}
