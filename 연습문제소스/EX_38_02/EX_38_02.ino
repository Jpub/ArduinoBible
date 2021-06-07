#include "SevSeg.h"

SevSeg sevseg;        // 7세그먼트 표시장치 제어 객체
unsigned long time_previous;    // 갱신 시간
int count = 0;        // 표시할 카운터값
int INTERVAL = 100;       // 0.1초 간격으로 카운터 증가

boolean PRESSED = HIGH;
int pin_button = A0;
boolean state_previous = !PRESSED;
boolean state_current;

int step = 1;

void setup() {
  byte dPins[] = {10, 11, 12, 13};    // 자리 선택핀
  byte sPins[] = {2, 3, 4, 5, 6, 7, 8, 9};  // 세그먼트 제어핀
  bool leadingZeros = false;    // 선행 영(leading zero) 없음
  bool disableDecPoint = false;   // 소수점 사용함

  sevseg.begin(COMMON_CATHODE, 4, dPins, sPins, true, false,
               leadingZeros, disableDecPoint); // 7세그먼트 제어 객체 초기화
  time_previous = millis();

  pinMode(pin_button, INPUT);
}

void loop() {
  state_current = digitalRead(pin_button);

  if (state_current == PRESSED) {
    if (state_previous == !PRESSED) {
      state_previous = PRESSED;
      step *= -1;
    }
  }
  else {
    state_previous = !PRESSED;
  }

  unsigned long time_current = millis();

  // INTERVAL 이상의 시간이 지나면 카운터를 증가시킴
  if (time_current - time_previous >= INTERVAL) {
    time_previous = time_current;

    count = count + step;
    if (count == 10000) {
      count = 0;
    }
    else if (count == -1) {
      count = 9999;
    }

    // 7세그먼트에 표시할 숫자 변경, 소수점 이하 1자리
    sevseg.setNumber(count, 1);
  }

  sevseg.refreshDisplay();      // 7세그먼트에 표시
}
