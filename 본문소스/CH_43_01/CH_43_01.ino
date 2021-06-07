#include <Adafruit_NeoPixel.h>

int PIN = 6;           // 네오픽셀 연결 핀
int NUMPIXELS = 24;     // 픽셀 수
int BRIGHTNESS = 5;     // 밝기 정도 [0 255]
int INTERVAL = 100;

Adafruit_NeoPixel ring(NUMPIXELS, PIN); // 네오픽셀 객체 생성

void setup() {
  ring.begin();         // 네오픽셀 객체 초기화
  ring.clear();         // 모든 픽셀을 끔
}

void loop() {
  for (int n = 0; n < NUMPIXELS; n++) { // 픽셀을 순서대로 켜기
    // 네오픽셀의 n번째 픽셀 색상을 RGB 개별 성분 값으로 설정
    ring.setPixelColor(n, 0, BRIGHTNESS, 0);
    ring.show();        // 네오픽셀로 데이터 전송

    delay(INTERVAL);
  }

  for (int n = 0; n < NUMPIXELS; n++) { // 픽셀을 순서대로 끄기
    // 네오픽셀의 n번째 픽셀 색상을 32비트 WRGB 값으로 설정
    ring.setPixelColor(n, ring.Color(0, 0, 0));
    ring.show();

    delay(INTERVAL);
  }
}
