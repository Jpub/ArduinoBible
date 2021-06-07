#include <Adafruit_SSD1306.h>
#include <splash.h>

#define SCREEN_WIDTH 128    // OLED x축 해상도
#define SCREEN_HEIGHT 64    // OLED y축 해상도

#define OLED_CLK  9
#define OLED_MOSI 10
#define OLED_RESET  11
#define OLED_DC 12
#define OLED_CS 13

// OLED 제어를 위한 객체 생성
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // OLED 객체 초기화 및 디스플레이 버퍼 할당
  if ( !display.begin(SSD1306_SWITCHCAPVCC) ) {
    while (1);        // 초기화 실패로 정지
  }
  display.clearDisplay();

  display.drawBitmap(     // 화면 가운데에 이미지 표시
    (display.width() - splash1_width) / 2,
    (display.height() - splash1_height) / 2,
    splash1_data, splash1_width, splash1_height, WHITE);

  display.display();      // 디스플레이 버퍼 화면에 나타내기
}

void loop() {
}
