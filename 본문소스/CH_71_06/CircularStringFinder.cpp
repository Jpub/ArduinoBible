#include <Arduino.h>
#include "CircularStringFinder.h"

CircularStringFinder::CircularStringFinder(byte _N) {
  N = _N;           // 버퍼 크기
  buffer = (char *)malloc(N);     // 메모리 할당
  clear();            // 초기화
}

CircularStringFinder::~CircularStringFinder() {
  if (buffer) {         // 메모리 해제
    free(buffer);
  }
}

void CircularStringFinder::restart() {  // 이전 설정으로 검색 다시 시작
  head = 0;
  tail = 0;
  search_status = STATE_KEY_SEARCHING;
}

void CircularStringFinder::clear() {  // 초기화
  head = 0;
  tail = 0;

  key = "";           // 시작 문자열과 종료 문자는 비어 있음
  terminator = 0;
  search_status = STATE_KEY_SEARCHING;
}

byte CircularStringFinder::length() {
  if (head == tail) {       // 초기 상태
    return 0;
  }
  else {
    return (tail + N - head ) % N;
  }
}

void CircularStringFinder::addCharacter(char ch) {
  buffer[tail] = ch;      // 문자 저장
  tail = (tail + 1) % N;      // 꼬리 위치 옮김

  if (tail == head) {       // 버퍼가 넘치는 경우 머리 위치 옮김
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

void CircularStringFinder::setKey(String _key, char _terminator) {
  clear();
  key = _key;       // 시작 문자열 설정
  terminator = _terminator;   // 종료 문자 설정
};

String CircularStringFinder::getKey() {
  return key;
}

char CircularStringFinder::getTerminator() {
  return terminator;
}

boolean CircularStringFinder::end_with_key() {
  byte key_len = key.length();
  if (key_len > length()) {     // 시작 문자열 길이가 버퍼 길이보다 긴 경우
    return false;
  }

  for (byte i = 0; i < key_len; i++) {  // 버퍼 내용이 시작 문자열로 끝나는지 검사
    char key_ch = key[key_len - 1 - i];
    byte buffer_index = (N + tail - 1 - i) % N;
    char buffer_ch = buffer[buffer_index];

    if (key_ch != buffer_ch) {
      return false;
    }
  }

  return true;
}

byte CircularStringFinder::add(char ch) { // 문자 추가 및 탐색
  if (search_status == STATE_KEY_SEARCHING) {     // 시작 문자열 탐색 중
    addCharacter(ch);
    if (end_with_key()) {     // 시작 문자열 발견
      head = 0;       // 버퍼 비움
      tail = 0;
      search_status = STATE_VALUE_SEARCHING;
    }
  }
  else if (search_status == STATE_VALUE_SEARCHING) {  // 값 입력 중
    if (ch == terminator) {   // 종료 문자 발견
      search_status = STATE_VALUE_FOUND;
    }
    else {            // 버퍼에 값 저장
      addCharacter(ch);
    }
  }

  return search_status;     // 현재 검색 상태 반환
}

byte CircularStringFinder::getSearchStatus() {
  return search_status;     // 현재 검색 상태 반환
}

String CircularStringFinder::getValue() { // 검색된 값 반환
  buffer[tail] = 0;
  String value = String(buffer);

  return value;
}
