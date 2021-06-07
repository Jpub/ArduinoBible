#include <Arduino.h>
#include "CircularStringFinder.h"

CircularStringFinder::CircularStringFinder(byte _N) {
  N = _N;           // 버퍼 크기
  buffer = (char *)malloc(N);   // 메모리 할당
  clear();            // 초기화
}

CircularStringFinder::~CircularStringFinder() {
  if (buffer) {       // 메모리 해제
    free(buffer);
  }
}

void CircularStringFinder::clear() {
  head = 0;
  tail = 0;
}

byte CircularStringFinder::length() {
  if (head == tail) {     // 초기 상태
    return 0;
  }
  else {
    return (tail + N - head ) % N;
  }
}

void CircularStringFinder::addCharacter(char ch) {
  buffer[tail] = ch;      // 문자 저장
  tail = (tail + 1) % N;      // 꼬리 위치 옮김

  if (tail == head) {     // 버퍼가 넘치는 경우 머리 위치 옮김
    head = (head + 1) % N;
  }
}

void CircularStringFinder::printInfo() {  // 정보 출력
  Serial.println(String("버퍼 크기\t\t: ") + N);
  Serial.println(String("머리, 꼬리\t: (") + head + ", " + tail + ")");
  Serial.println(String("문자열 길이\t: ") + length());
  Serial.print("문자열\t\t: \"");
  for (int i = head; i < head + length(); i++) {
    Serial.print(buffer[i % N]);
  }
  Serial.println("\"");
  Serial.println();
}
