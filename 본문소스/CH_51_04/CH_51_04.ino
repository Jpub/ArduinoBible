#include <Wire.h>
#include <RtcDS1307.h>

RtcDS1307<TwoWire> RTC(Wire);    // DS1307 RTC 칩 객체 생성

int pin_LED = 13;       // LED 연결 핀
boolean state = false;      // LED 상태

void blink() {        // 외부 인터럽트 서비스 루틴
  state = !state;         // LED 상태 반전
  digitalWrite(pin_LED, state);     // 현재 LED 상태 출력
}

void setup () {
  RTC.Begin();        // DS1307 RTC 칩 연결 초기화

  pinMode(pin_LED, OUTPUT);   // LED 연결 핀을 출력으로 설정
  digitalWrite(pin_LED, state);   // LED 초기 상태

  // 1Hz의 구형파가 출력되도록 설정
  RTC.SetSquareWavePin(DS1307SquareWaveOut_1Hz);

  // 디지털 2번 핀으로 입력되는 정현파의 상승 및 하강 에지에서(CHANGE)
  // 'blink' 함수가 호출되도록 인터럽트 처리 함수 등록
  attachInterrupt(digitalPinToInterrupt(2), blink, CHANGE);
}

void loop () {
}
