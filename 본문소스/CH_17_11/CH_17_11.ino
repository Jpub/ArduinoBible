#include <TimerOne.h>

int LED1 = 13, LED2 = 12;     // LED 연결 핀
boolean state1 = false, state2 = false;   // LED 상태

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);

  Timer1.attachInterrupt(blink);    // 콜백 함수 등록
  Timer1.initialize(500000);    // 마이크로초 단위
}

void loop() {
  state1 = !state1;     // 1초 간격 점멸
  digitalWrite(LED1, state1);

  delay(1000);        // 1초 대기
}

void blink() {        // 0.5초 간격 점멸
  state2 = !state2;
  digitalWrite(LED2, state2);
}
