#include <Arduino.h>       // 아두이노 헤더 파일 포함

int main(void) {
  init();               // 아두이노 환경 초기화

  setup();            // 사용자 초기화 함수

  while (1) {
    loop();           // 사용자 반복 처리 함수
  }

  return 0;
}

void setup() {
  pinMode(13, OUTPUT);      // LED 연결 핀을 출력으로 설정
}

void loop() {
  digitalWrite(13, HIGH);       // LED 연결 핀으로 HIGH 출력
  delay(1000);        // 1초 대기
  digitalWrite(13, LOW);      // LED 연결 핀으로 LOW 출력
  delay(1000);        // 1초 대기
}
