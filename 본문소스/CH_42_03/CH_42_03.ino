#include <Adafruit_SSD1306.h>

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

  display.drawLine(0, 0, 127, 63, WHITE); // 직선
  display.drawLine(127, 0, 0, 63, WHITE);

  for (int r = 30; r >= 5; r -= 5) {
    if (r % 10 == 0) {      // 채워진 원
      display.fillCircle(64, 32, r, WHITE);
    }
    else {          // 빈 원, 원 내부를 강제로 지움
      display.fillCircle(64, 32, r, BLACK);
    }
  }

  display.display();      // 디스플레이 버퍼 화면에 나타내기
}

void loop() {
}
