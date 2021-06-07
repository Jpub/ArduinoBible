int LED1 = 13, LED2 = 12;     // LED 연결 핀
int pin_button = 2;       // 버튼 연결 핀
boolean state1 = false, state2 = false;   // LED 상태
unsigned long time_previous = 0;

boolean PRESSED = HIGH;
boolean state_previous = !PRESSED;
boolean state_current;

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);
  pinMode(pin_button, INPUT);     // 버튼 연결 핀을 입력으로 설정
}

void loop() {
  unsigned long time_current = millis();  // 현재까지의 실행 시간

  // LED를 반전시킨 이전 시간 이후 1초 이상 시간이 지난 경우
  if (time_current - time_previous >= 1000) {
    time_previous = time_current;
    state1 = !state1;       // 13번 핀 LED 상태 반전
    digitalWrite(LED1, state1);     // 13번 핀 LED 상태 표시
  }

  state_current = get_button_state(pin_button);  // 버튼 상태 읽기

  if (state_current == PRESSED) {
    if (state_previous == !PRESSED) {
      state_previous = PRESSED;   // 이전 상태 갱신

      state2 = !state2;       // 12번 핀 LED 상태 반전
      digitalWrite(LED2, state2);     // 12번 핀 LED 상태 표시
    }
  }
  else {
    state_previous = !PRESSED;
  }
}

boolean get_button_state(byte pin_no) {
  if (digitalRead(pin_no) == PRESSED) { // 첫 번째 버튼 검사
    delay(20);
    if (digitalRead(pin_no) == PRESSED) { // 두 번째 버튼 검사
      return PRESSED;
    }
  }
  return !PRESSED;
}
