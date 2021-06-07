#include <Adafruit_NeoPixel.h>

int PIN = 6;           // 네오픽셀 연결 핀
int NUMPIXELS = 24;       // 픽셀 수
int INTERVAL = 10;      // 색상이 변하는 시간 간격

Adafruit_NeoPixel ring(NUMPIXELS, PIN); // 네오픽셀 객체 생성

void setup() {
  ring.begin();         // 네오픽셀 객체 초기화
  ring.clear();         // 모든 픽셀을 끔
  ring.setBrightness(20);     // 전체적인 밝기 조정 [0 255]
}

void loop() {
  // 시작 픽셀의 색상값을 변경하여 색상이 이동하는 효과를 얻음
  for (uint16_t hue = 0; hue < 65536; hue += 256) {
    rainbow(hue);
    delay(INTERVAL);
  }
}

void rainbow(uint16_t start_hue) {
  // 전체 색상값의 범위를 정해진 픽셀 수에 나누어 표현
  uint16_t hue_step = 65536 / NUMPIXELS;

  for (int n = 0; n < NUMPIXELS; n++) {
    // 65536 이상의 값이 나올 수 있지만, 오버플로에 의해 자동으로 조정된다.
    uint16_t current_hue = hue_step * n + start_hue;
    uint32_t current_color = ring.ColorHSV(current_hue);
    uint32_t corrected_color = ring.gamma32(current_color);

    ring.setPixelColor(n, corrected_color);
  }
  ring.show();
}
