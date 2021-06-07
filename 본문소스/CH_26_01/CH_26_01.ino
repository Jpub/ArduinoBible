#include <hidboot.h>

/*****************************************
   마우스 동작 처리를 위한 클래스 정의 시작
*****************************************/
class MouseActionParser : public MouseReportParser {
  protected:
    void OnMouseMove(MOUSEINFO *mi);
    void OnLeftButtonUp(MOUSEINFO *mi);
    void OnLeftButtonDown(MOUSEINFO *mi);
    void OnRightButtonUp(MOUSEINFO *mi);
    void OnRightButtonDown(MOUSEINFO *mi);
    void OnMiddleButtonUp(MOUSEINFO *mi);
    void OnMiddleButtonDown(MOUSEINFO *mi);
};

void MouseActionParser::OnMouseMove(MOUSEINFO *mi) {
  Serial.print("마우스 이동 (x, y) : (");
  Serial.println(mi->dX + String(", ") + mi->dY + ")");
};

void MouseActionParser::OnLeftButtonUp(MOUSEINFO *mi) {
  Serial.println("왼쪽 버튼 뗌");
};

void MouseActionParser::OnLeftButtonDown(MOUSEINFO *mi) {
  Serial.println("왼쪽 버튼 누름");
};

void MouseActionParser::OnRightButtonUp(MOUSEINFO *mi) {
  Serial.println("오른쪽 버튼 뗌");
};

void MouseActionParser::OnRightButtonDown(MOUSEINFO *mi) {
  Serial.println("오른쪽 버튼 누름");
};

void MouseActionParser::OnMiddleButtonUp(MOUSEINFO *mi) {
  Serial.println("가운데 버튼 뗌");
};

void MouseActionParser::OnMiddleButtonDown(MOUSEINFO *mi) {
  Serial.println("가운데 버튼 누름");
};
/*****************************************
   마우스 동작 처리를 위한 클래스 정의 끝
*****************************************/

USB Usb;            // USB 연결을 위한 객체
// USB를 통해 HID 프로토콜을 사용하는 마우스 연결
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);

MouseActionParser parser;   // 마우스 동작 처리 객체 생성

void setup() {
  Serial.begin(115200);

  Usb.Init();           // USB 연결 초기화
  delay(200);

  // 마우스 동작 처리 객체 등록
  HidMouse.SetReportParser(0, (HIDReportParser*)&parser);
  Serial.println("* 시작... 마우스를 움직이거나 버튼을 누르세요.");
}

void loop() {
  Usb.Task();         // USB 장치 연결 및 연결 해제 처리
}
