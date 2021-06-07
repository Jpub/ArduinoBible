#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED x축 해상도
#define SCREEN_HEIGHT 64    // OLED y축 해상도

#define OLED_CLK  9
#define OLED_MOSI 10
#define OLED_RESET  11
#define OLED_DC 12
#define OLED_CS 13

const uint8_t PROGMEM heart1 [] = {
  0x66, 0x99, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18
};

const uint8_t PROGMEM heart2 [] = {
  0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18
};

// OLED 제어를 위한 객체 생성
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  if ( !display.begin(SSD1306_SWITCHCAPVCC) ) {
    while (1);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.drawBitmap(5, 20, heart1, 8, 8, WHITE);
  display.setCursor(20, 21);
  display.print("I Love Arduino~");
  display.drawBitmap(115, 20, heart2, 8, 8, WHITE);

  display.display();
}

void loop() {
}
