#include <Ticker.h>

void blink1();        // 콜백함수 선언
void blink2();

int LED1 = 13, LED2 = 12;   // LED 연결 핀
boolean state1 = false, state2 = false; // LED 상태

Ticker ticker1(blink1, 1000); // 1초 간격으로 blink1 함수를 호출하는 객체
Ticker ticker2(blink2, 500);  // 0.5초 간격으로 blink2 함수를 호출하는 객체

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);

  ticker1.start();        // Ticker 객체의 시간 계산 시작
  ticker2.start();
}

void loop() {
  ticker1.update();     // 시간 업데이트 및 콜백 함수 호출
  ticker2.update();
}

void blink1() {       // 1초 간격 점멸
  state1 = !state1;
  digitalWrite(LED1, state1);
}

void blink2() {       // 0.5초 간격 점멸
  state2 = !state2;
  digitalWrite(LED2, state2);
}
