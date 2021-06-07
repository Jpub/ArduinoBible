int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};   // LED가 연결된 핀 배열
byte index = 0;       // 핀/LED 번호 인덱스

void setup() {
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {     // LED에 상태 표시
    if (i == index) {     // 1개만 켬
      digitalWrite(pins[i], HIGH);
    }
    else {            // 나머지 7개는 끔
      digitalWrite(pins[i], LOW);
    }
  }

  index = (index + 1) % 8;    // 0~7을 반복
  delay(1000);        // 1초 대기
}
