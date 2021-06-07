boolean PRESSED = LOW;     // 버튼이 눌러진 상태에서의 입력값
int pin_button = 9;       // 버튼이 연결된 핀
int press_count = 0;      // 버튼을 누른 횟수
boolean state_previous = !PRESSED;  // 버튼의 이전 상태
boolean state_current;      // 버튼의 현재 상태

void setup() {
  Serial.begin(9600);       // 시리얼 통신 초기화
  // 버튼 연결 핀을 내장 풀업 저항을 사용하는 입력으로 설정
  pinMode(pin_button, INPUT_PULLUP);
}

void loop() {
  // 버튼을 짧은 시간 간격으로 두 번 읽어 모두 눌러진 값이 나오는지 검사
  state_current = get_button_state(pin_button);

  if (state_current == PRESSED) {   // 현재 눌러진 상태
    if (state_previous == !PRESSED) {   // 이전에 눌러지지 않은 상태
      press_count++;
      state_previous = PRESSED;   // 이전 상태 갱신

      Serial.print("버튼을 ");     // 메시지 출력
      Serial.println(String(press_count) + "번 눌렀습니다.");
    }
  }
  else {
    state_previous = !PRESSED;
  }
}

boolean get_button_state(byte pin_no) {
  if (digitalRead(pin_no) == PRESSED) { // 첫 번째 버튼 검사
    delay(10);
    if (digitalRead(pin_no) == PRESSED) { // 두 번째 버튼 검사
      return PRESSED;
    }
  }
  return !PRESSED;
}
