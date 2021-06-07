int LEDs[] = { 6, 7, 8, 9, 10, 11, 12, 13 };  // LED 연결 핀

void setup() {
  Serial.begin(9600);       // 블루투스 모듈과의 시리얼 통신 초기화

  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LOW);   // 디폴트 상태는 꺼진 상태
  }
}

void loop() {
  if (Serial.available()) {     // 블루투스를 통한 데이터 수신 확인
    char ch = Serial.read();    // 한 문자 읽기
    Serial.print(String(ch) + " : ");

    if (ch >= '0' && ch <= '8') {     // 0~8 사이 문자 수신
      int count = ch - '0';     // 문자를 숫자로 변환
      Serial.println(String(count) + "개 LED를 켭니다.");

      for (int i = 0; i < 8; i++) {     // 해당 개수만큼 LED 켜기
        if (i < count) {
          digitalWrite(LEDs[i], HIGH);
        }
        else {
          digitalWrite(LEDs[i], LOW);
        }
      }
    }
    else {          // 잘못된 데이터 수신
      Serial.println("잘못된 데이터가 수신되었습니다.");
    }
  }
}
