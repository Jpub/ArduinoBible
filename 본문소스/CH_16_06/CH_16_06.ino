#include <BlinkLED.h>

BlinkLED blink;    // BlinkLED 객체 생성

void setup() {
  blink.init(13, 500);  // 13번 핀 LED를 0.5초 간격으로 점멸하도록 초기화
}

void loop() {
  blink.update();   // 13번 핀 LED 상태 갱신
}
