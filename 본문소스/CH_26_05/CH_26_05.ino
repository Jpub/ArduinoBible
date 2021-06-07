#include <hidboot.h>

boolean compare_it = false;    // 검사 시점 결정
String test_string, input_string;   // 테스트 문자열과 입력 문자열
int test_string_len;      // 테스트 문자열 길이
int MIN_LEN = 3, MAX_LEN = 10;  // 테스트 문자열 최소, 최대 길이

unsigned long time_previous, time_current;
unsigned long MS_PER_CH = 500;  // 문자당 입력 제한 시간 (밀리초)
USB Usb;          // USB 연결을 위한 객체

#include "parser.h"

// USB를 통해 HID 프로토콜을 사용하는 키보드 연결
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);
KeyboardTypingParser keyboardParser;  // 키보드 동작 처리 객체 생성

void make_test_string() {   // 테스트 문자열 생성
  // 테스트 문자열 길이 랜덤 결정
  test_string_len = random(MAX_LEN - MIN_LEN + 1) + MIN_LEN;
  test_string = "";
  for (int i = 0; i < test_string_len; i++) {
    int big_small = random(2);    // 대소문자 결정
    int c = random(26);     // 알파벳 결정
    test_string += char(big_small ? 'A' + c : 'a' + c);
  }
  Serial.println("* 아래 알파벳을 입력하세요.");
  Serial.println("\t\t" + test_string);
  input_string = "";
  Serial.print("\t\t");     // 입력 문자열 표시 위치 조정
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A0));   // 난수 발생기 초기화

  Usb.Init();         // USB 연결 초기화
  delay(200);

  // 키보드 동작 처리 객체 등록
  HidKeyboard.SetReportParser(0, (HIDReportParser*)&keyboardParser);

  make_test_string();
}

void loop() {
  Usb.Task();         // USB 장치 연결 및 연결 해제 처리

  if (compare_it) {     // 엔터키를 누른 경우
    time_current = millis();    // 입력 종료 시각
    unsigned long interval = time_current - time_previous;

    Serial.println(" => 입력한 알파벳\t: " + input_string);
    Serial.print(" => 소요 시간\t: ");
    Serial.print(interval / 1000.0, 2);
    Serial.print("초 ");

    if (interval > MS_PER_CH * test_string_len) { // 시간 검사
      Serial.println("(제한 시간을 초과했습니다.)");
    }
    else {
      Serial.println("(시간 내에 입력했습니다.)");
    }

    if (input_string.equals(test_string)) {     // 입력 내용 검사
      Serial.println(" => 정확히 입력했습니다.");
    }
    else {
      Serial.println(" => 잘못 입력했습니다.");
    }
    Serial.println();

    compare_it = false;     // 다시 시작
    make_test_string();
  }
}
