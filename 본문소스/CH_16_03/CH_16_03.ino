unsigned long blink_previous;    // 이전 점멸 시간
boolean blink_state;      // 현재 LED 상태
int blink_pin;        // LED 연결 핀
int blink_interval;     // LED 점멸 간격

void blink_init(int pin, int interval, boolean state = false) {
  blink_pin = pin;
  blink_interval = interval;
  blink_state = state;      // 디폴트값은 꺼진 상태
  blink_previous = millis();

  pinMode(blink_pin, OUTPUT);   // LED 연결 핀 출력으로 설정
  digitalWrite(blink_pin, blink_state); // LED에 초기 상태 출력
}

void blink_update() {
  unsigned long blink_current = millis(); // 현재 시각

  // LED를 반전시켜야 하는 경우
  if (blink_current - blink_previous >= blink_interval) {
    blink_previous = blink_current; // 마지막 반전 시간 갱신
    blink_state = !blink_state;   // LED 상태 반전
    digitalWrite(blink_pin, blink_state); // 현재 LED 상태 출력
  }
}

void setup() {
  blink_init(13, 500);      // LED 상태 초기화
}

void loop() {
  blink_update();       // LED 상태 갱신
}
