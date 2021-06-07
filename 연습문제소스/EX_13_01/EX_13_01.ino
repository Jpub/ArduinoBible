boolean PRESSED = LOW;     // 버튼이 눌러진 상태에서의 입력값
boolean state_previous = !PRESSED;  // 버튼의 이전 상태
boolean state_current;      // 버튼의 현재 상태

boolean state_LED = true;

void setup() {
  Serial.begin(9600);       // 시리얼 통신 초기화
  pinMode(9, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, state_LED);
}

void loop() {
  state_current = digitalRead(9);     // 버튼 상태 읽기

  if (state_current == PRESSED) {   // 현재 눌러진 상태
    if (state_previous == !PRESSED) {   // 이전에 눌러지지 않은 상태
      state_previous = PRESSED;   // 이전 상태 갱신

      state_LED = !state_LED;
      digitalWrite(13, state_LED);
      Serial.print("LED 상태를 반전시킵니다 : ");
      Serial.println(state_LED ? "켜짐" : "꺼짐");
    }
    delay(50);       // 디바운싱
  }
  else {
    state_previous = !PRESSED;
  }
}
