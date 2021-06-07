// #define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

Encoder encoder(3, 2);      // 인코더 객체 생성
long position = -999;     // 이전 위치값

void setup() {
  Serial.begin(9600);
  Serial.println("* 위치를 0으로 초기화합니다.");
}

void loop() {
  long newPosition = encoder.read();
  if (newPosition != position) {
    position = newPosition;
    Serial.println(String("현재 위치 : ") + position);
  }

  // delay(100);
}
