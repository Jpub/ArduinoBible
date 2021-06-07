#include <Ticker.h>

int pin_LED = 13;
boolean LED_state = false;
Ticker ticker;         // Ticker 객체

void setup() {
  pinMode(pin_LED, OUTPUT);     // 출력으로 설정
  digitalWrite(pin_LED, LED_state);   // 꺼진 상태로 시작

  ticker.attach(1, blinking);     // 1초에 한 번 호출되는 함수 설정
}

void blinking() {         // 콜백 함수
  LED_state = !LED_state;     // LED 상태 반전
  digitalWrite(pin_LED, LED_state);   // LED 상태 표시
}

void loop() {
}
