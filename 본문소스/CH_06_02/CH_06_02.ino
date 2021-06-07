#include <Arduino.h>      // 아두이노 헤더 파일 포함

int main(void) {
  init();             // 아두이노 환경 초기화

  pinMode(13, OUTPUT);      // LED 연결 핀을 출력으로 설정

  while (1) {
    digitalWrite(13, HIGH);   // LED 연결 핀으로 HIGH 출력
    delay(1000);        // 1초 대기
    digitalWrite(13, LOW);    // LED 연결 핀으로 LOW 출력
    delay(1000);        // 1초 대기
  }

  return 0;
}
