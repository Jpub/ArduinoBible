#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED x축 해상도
#define SCREEN_HEIGHT 64    // OLED y축 해상도

// OLED 제어를 위한 객체 생성
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

void setup() {
  // OLED 객체 초기화 및 디스플레이 버퍼 할당, I2C 주소 지정
  if ( !display.begin(SSD1306_SWITCHCAPVCC, 0x3C) ) {
    while (1);        // 초기화 실패로 정지
  }
  display.clearDisplay();     // 디스플레이 버퍼 지우기
  display.setTextColor(WHITE);    // 텍스트 색깔 지정
  display.print("Hello OLED Display~"); // 문자열 출력
  display.display();      // 디스플레이 버퍼 화면에 나타내기
}

void loop() {
}
