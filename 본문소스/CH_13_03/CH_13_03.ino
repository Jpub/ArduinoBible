int N = 2;            // 버튼/LED 개수
int pin_button[] = {4, 5};      // 버튼 연결 핀
int pin_LED[] = {2, 3};     // LED 연결 핀

void setup() {
  for (int i = 0; i < N; i++) {
    pinMode(pin_button[i], INPUT);  // 버튼 연결 핀을 입력으로 설정
    pinMode(pin_LED[i], OUTPUT);  // LED 연결 핀을 출력으로 설정
  }
}

void loop() {
  for (int i = 0; i < N; i++) {
    boolean state = digitalRead(pin_button[i]); // 버튼 상태 읽기
    digitalWrite(pin_LED[i], state);      // LED로 상태 출력
  }
}
