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
  state_current = digitalRead(pin_button);  // 버튼 상태 읽기

  if (state_current == PRESSED) {   // 현재 눌러진 상태
    if (state_previous == !PRESSED) {   // 이전에 눌러지지 않은 상태
      press_count++;
      state_previous = PRESSED;   // 이전 상태 갱신

      Serial.print("버튼을 ");     // 메시지 출력
      Serial.println(String(press_count) + "번 눌렀습니다.");
    }
    // delay(50);       // 디바운싱
  }
  else {
    state_previous = !PRESSED;
  }
}
