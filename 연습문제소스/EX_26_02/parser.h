class KeyboardTypingParser : public KeyboardReportParser {
protected:
  void OnKeyDown(uint8_t mod, uint8_t key);
};

void KeyboardTypingParser::OnKeyDown(uint8_t mod, uint8_t key) {
  MODIFIERKEYS m;         // 모디파이어 키 상태
  *((uint8_t*)&m) = mod;

  uint8_t c = OemToAscii(mod, key); // 아스키코드 값으로 변환
  if (c) {            // 화면 출력 가능 문자인 경우
    if (input_string.length() == 0) {
      time_previous = millis();   // 처음 입력 시점에서 시간 측정 시작
    }

    if (key != 40) {      // 엔터키가 아닌 경우
      Serial.print((char)c);    // 화면 출력
      input_string += (char)c;    // 입력 문자열에 추가
    }
    else {          // 엔터키인 경우
      Serial.println();
      compare_it = true;    // 검사 시작
    }
  }
}
