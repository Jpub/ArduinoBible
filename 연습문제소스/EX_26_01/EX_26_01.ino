#include <hidboot.h>

int positionX = 100, positionY = 100;
/*****************************************
*  마우스 동작 처리를 위한 클래스 정의 시작
*****************************************/
class MouseActionParser : public MouseReportParser {
protected:
  void OnMouseMove(MOUSEINFO *mi);
};

void MouseActionParser::OnMouseMove(MOUSEINFO *mi) {
  positionX += mi->dX;
  positionY += mi->dY;

  if(positionX < 0){
    positionX = 0;
  }
  if(positionX > 200){
    positionX = 200;
  }
  if(positionY < 0){
    positionY = 0;
  }
  if(positionY > 200){
    positionY = 200;
  }

  Serial.println(String(positionX) + '\t' + positionY);
};
/*****************************************
*  마우스 동작 처리를 위한 클래스 정의 끝
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
}

void loop() {
  Usb.Task();         // USB 장치 연결 및 연결 해제 처리
}
