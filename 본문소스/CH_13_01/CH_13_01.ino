int pins[] = {2, 3, 4, 5};      // 버튼이 연결된 핀 배열

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화
  for (int i = 0; i < 4; i++) {   // 버튼 연결 핀을 입력으로 설정
    pinMode(pins[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {   // 4개 버튼의 상태 읽기
    boolean state = digitalRead(pins[i]); // 버튼 상태 읽기

    if (state) {        // 버튼 상태에 따른 메시지 출력
      Serial.print("O ");
    }
    else {
      Serial.print("X ");
    }
  }
  Serial.println();       // 줄바꿈

  delay(1000);        // 1초 대기
}
