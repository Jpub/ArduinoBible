boolean PRESSED = HIGH;     // 버튼이 눌러진 상태에서의 입력값
boolean state_previous = !PRESSED;  // 버튼의 이전 상태
boolean state_current;      // 버튼의 현재 상태

int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};   // LED가 연결된 핀 배열
int pin_btn = 10;
byte index = 0;       // 핀/LED 번호 인덱스

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
  pinMode(pin_btn, INPUT);

  show_LED_pattern();
}

void show_LED_pattern() {
  for (int i = 0; i < 8; i++) {     // LED에 상태 표시
    if (i == index) {     // 1개만 켬
      digitalWrite(pins[i], HIGH);
    }
    else {            // 나머지 7개는 끔
      digitalWrite(pins[i], LOW);
    }
  }
}

void loop() {
  state_current = digitalRead(pin_btn);     // 버튼 상태 읽기

  if (state_current == PRESSED) {   // 현재 눌러진 상태
    if (state_previous == !PRESSED) {   // 이전에 눌러지지 않은 상태
      state_previous = PRESSED;   // 이전 상태 갱신

      index = (index + 1) % 8;
      show_LED_pattern();
    }
    delay(50);       // 디바운싱
  }
  else {
    state_previous = !PRESSED;
  }
}
