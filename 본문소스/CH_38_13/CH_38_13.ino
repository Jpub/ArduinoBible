#include <LedControl.h>

// 객체 생성 (DIN, CS(LOAD), CLK, 모듈 수)
LedControl segment8 = LedControl(12, 11, 10, 1);

void setup() {
  segment8.shutdown(0, false);    // 정상 동작 모드
  segment8.setIntensity(0, 5);    // 밝기 설정
  segment8.clearDisplay(0);     // LED 매트릭스 끄기

  for (int digit = 0; digit < 8; digit++) {   // 숫자 출력
    segment8.setDigit(0, digit, digit, false);
  }
}

void loop() {
  // 잔상효과는 아두이노가 신경 쓰지 않아도 된다.
}
