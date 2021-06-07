#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED x축 해상도
#define SCREEN_HEIGHT 64    // OLED y축 해상도

#define OLED_CLK  9
#define OLED_MOSI 10
#define OLED_RESET  11
#define OLED_DC 12
#define OLED_CS 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int vr, vr_old = 0;

void setup() {
  if ( !display.begin(SSD1306_SWITCHCAPVCC) ) {
    while (1);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(5, 10);
  display.print("Variable R");

  display.setCursor(15, 35);
  display.print(vr_old);

  display.display();
}

void loop() {
  vr = analogRead(A0);

  if (vr != vr_old) {
    display.setTextColor(BLACK);
    display.setCursor(15, 35);
    display.print(vr_old);

    display.setTextColor(WHITE);
    display.setCursor(15, 35);
    display.print(vr);

    vr_old = vr;

    display.display();
  }

  delay(1000);
}
