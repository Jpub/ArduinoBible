#include <Encoder.h>

int pins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };  // LED 연결 핀
int index = 0;        // 켜지는 LED 위치

const int MIN_MOVE = 4;     // LED 이동을 위한 인코더 위치 차이
Encoder encoder(3, 2);      // 인코더 객체 생성
long position = 0;      // 이전 위치

void setup() {
  for (int i = 0; i < 8; i++) {   // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
  show_LED();       // LED 표시
}

void show_LED() {
  for (int i = 0; i < 8; i++) {   // 하나만 켜고 나머지는 끔
    digitalWrite(pins[i], i == index);
  }
}

void loop() {
  long newPosition = encoder.read();  // 위치 알아내기
  long diff = newPosition - position; // 위치 차이

  if (diff >= MIN_MOVE || diff <= -MIN_MOVE) {
    index = index + diff / MIN_MOVE;  // LED를 움직이는 양
    // 음수값인 경우도 처리하기 위해 8을 더해서 나머지를 구함
    index = (index + 8) % 8;

    show_LED();

    position = newPosition;
  }
}
