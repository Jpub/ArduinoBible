boolean PRESSED = LOW;    // 버튼이 눌러진 상태에서의 입력값
int pin_button = 9;       // 버튼이 연결된 핀
int press_count = 0;

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화
  // 버튼 연결 핀을 내장 풀업 저항을 사용하는 입력으로 설정
  pinMode(pin_button, INPUT_PULLUP);
}

void loop() {
  boolean state = digitalRead(pin_button);  // 버튼 상태 읽기

  if (state == PRESSED) {     // 버튼이 눌러진 경우
    press_count++;      // 버튼을 누른 횟수 증가
    Serial.print("버튼을 ");     // 메시지 출력
    Serial.println(String(press_count) + "번 눌렀습니다.");
  }

  delay(100);         // 0.1초마다 버튼 상태 검사
}
