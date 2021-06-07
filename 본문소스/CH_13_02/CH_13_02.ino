int pin_button = 9;       // 버튼이 연결된 핀

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화
  // 버튼 연결 핀을 내장 풀업 저항을 사용하는 입력으로 설정
  pinMode(pin_button, INPUT_PULLUP);
}

void loop() {
  boolean state = digitalRead(pin_button);  // 버튼 상태 읽기

  Serial.print(String('\'') + state + "\' : ");
  if (state) {          // 버튼 상태에 따른 메시지 출력
    Serial.println("버튼을 누르지 않았습니다.");
  }
  else {
    Serial.println("버튼을 눌렀습니다.");
  }

  delay(1000);        // 1초 대기
}
