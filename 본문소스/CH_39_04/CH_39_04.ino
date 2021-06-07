#include <LedControl.h>

// 객체 생성 (DIN, CS(LOAD), CLK, 모듈 수)
LedControl matrix = LedControl(12, 11, 10, 1);

byte smile[] = {         // 사용자 정의 문자 데이터
  B00111100, B01000010, B10100101, B10000001,
  B10100101, B10011001, B01000010, B00111100
};

void setup() {
  matrix.shutdown(0, false);    // 정상 동작 모드
  matrix.setIntensity(0, 5);    // 밝기 설정
  matrix.clearDisplay(0);       // LED 매트릭스 끄기

  for (int r = 0; r < 8; r++) {   // 스마일 문자 데이터 출력
    matrix.setRow(0, r, smile[r]);
  }
}

void loop() {
  // 잔상효과는 아두이노가 신경 쓰지 않아도 된다.
}
