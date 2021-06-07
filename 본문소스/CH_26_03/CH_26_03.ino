#include <hidboot.h>
#include "parsers.h"      // 사용자 정의 클래스

USB Usb;            // USB 연결을 위한 객체

// USB를 통해 HID 프로토콜을 사용하는 키보드 & 마우스 연결
HIDBoot < USB_HID_PROTOCOL_MOUSE | USB_HID_PROTOCOL_KEYBOARD > HidMK(&Usb);

KeyboardActionParser keyboardParser;  // 키보드 동작 처리 객체 생성
MouseActionParser mouseParser;  // 마우스 동작 처리 객체 생성

void setup() {
  Serial.begin(115200);

  Usb.Init();           // USB 연결 초기화
  delay(200);

  // 키보드와 마우스 동작 처리 객체 등록
  HidMK.SetReportParser(0, (HIDReportParser*)&keyboardParser);
  HidMK.SetReportParser(1, (HIDReportParser*)&mouseParser);

  Serial.println("* 시작...");
}

void loop() {
  Usb.Task();         // USB 장치 연결 및 연결 해제 처리
}
