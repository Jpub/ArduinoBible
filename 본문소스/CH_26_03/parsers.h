/*****************************************
*  마우스 동작 처리를 위한 클래스 정의 시작
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
*  마우스 동작 처리를 위한 클래스 정의 끝
*****************************************/

/*****************************************
키보드 동작 처리를 위한 클래스 정의 시작
*****************************************/
class KeyboardActionParser : public KeyboardReportParser {
  void PrintKey(uint8_t mod, uint8_t key);  // 키값 출력

protected:
  void OnKeyDown(uint8_t mod, uint8_t key);
  void OnKeyUp(uint8_t mod, uint8_t key);
};

void KeyboardActionParser::PrintKey(uint8_t m, uint8_t key) {
  MODIFIERKEYS mod;       // 모디파이어 키 상태
  *((uint8_t*)&mod) = m;

  // 왼쪽 모디파이어 키
  Serial.print((mod.bmLeftCtrl == 1) ? "Ctrl " : " ");
  Serial.print((mod.bmLeftShift == 1) ? "Shift " : " ");
  Serial.print((mod.bmLeftAlt == 1) ? "Alt " : " ");

  Serial.print(" << ");
  Serial.print(key);      // OEM 키값 출력

  // 아스키 문자로 변환 가능한 키가 눌러진 경우 아스키 문자 출력
  uint8_t c = OemToAscii(m, key);   // 아스키 문자로 변환
  if (c) {              // 아스키 문자가 존재하는 경우
    Serial.print(String(", ") + (char)c);
  }
  Serial.print(" >> ");

  // 오른쪽 모디파이어 키
  Serial.print((mod.bmRightCtrl == 1) ? "Ctrl" : " ");
  Serial.print((mod.bmRightShift == 1) ? "Shift" : " ");
  Serial.print((mod.bmRightAlt == 1) ? "Alt" : " ");
  Serial.println();
};

void KeyboardActionParser::OnKeyDown(uint8_t mod, uint8_t key) {
  Serial.print("키 누름\t: ");
  PrintKey(mod, key);
}

void KeyboardActionParser::OnKeyUp(uint8_t mod, uint8_t key) {
  Serial.print("키 뗌\t: ");
  PrintKey(mod, key);
}
/*****************************************
키보드 동작 처리를 위한 클래스 정의 끝
*****************************************/
