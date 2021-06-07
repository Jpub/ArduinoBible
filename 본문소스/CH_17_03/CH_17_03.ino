int LED1 = 13, LED2 = 12;    // LED 연결 핀
int pin_button = 2;     // 버튼 연결 핀
boolean state1 = false, state2 = false; // LED 상태

void setup() {
  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);
  pinMode(pin_button, INPUT);   // 버튼 연결 핀을 입력으로 설정
}

void loop() {
  digitalWrite(LED1, state1);   // 13번 핀 LED 상태 표시
  delay(1000);        // 1초 대기
  state1 = !state1;     // 13번 핀 LED 상태 반전

  if (digitalRead(pin_button)) {    // 버튼이 눌러진 경우
    state2 = !state2;     // 12번 핀 LED 상태 반전
    digitalWrite(LED2, state2);   // 12번 핀 LED 상태 표시
  }
}
