#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     // OLED x축 해상도
#define SCREEN_HEIGHT 64    // OLED y축 해상도

#define OLED_CLK    14
#define OLED_MOSI   13
#define OLED_RESET    2
#define OLED_DC   0
#define OLED_CS   4

// OLED 제어를 위한 객체 생성
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // OLED 객체 초기화 및 디스플레이 버퍼 할당
  if ( !display.begin(SSD1306_SWITCHCAPVCC) ) {
    while (1);        // 초기화 실패로 정지
  }
  display.clearDisplay();       // 디스플레이 버퍼 지우기
  display.setTextColor(WHITE);    // 텍스트 색깔 지정

  int y = 0;          // 문자열을 출력할 y축 위치
  for (int scale = 1; scale < 4; scale++) {
    display.setTextSize(scale);     // 텍스트 배율 지정
    display.setCursor(0, y);    // 텍스트 커서 위치 변경, 픽셀 단위

    display.print("Size:");
    display.print(scale);

    y = y + 8 * scale + 2;    // 2픽셀 여백
  }
  display.display();      // 디스플레이 버퍼 화면에 나타내기
}

void loop() {
}
