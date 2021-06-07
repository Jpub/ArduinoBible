int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};   // LED가 연결된 핀 배열
char TERMINATOR = '\n';     // 문자열 종료 문자
String buffer = "";       // 문자열 저장 버퍼
boolean process_it = false;     // 문자열 처리 여부

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  while (Serial.available() > 0) {    // 데이터 수신
    char ch = Serial.read();    // 데이터 읽기

    if (ch == TERMINATOR) {     // 문자열 종료 문자인 경우
      process_it = true;      // 문자열 처리 지시
    }
    else {          // 이외의 문자인 경우
      buffer = buffer + ch;     // 버퍼에 문자 저장
    }
  }

  if (process_it) {     // 저장된 문자열을 처리하는 경우
    Serial.print("\'" + buffer + "\'\t : ");  // 입력 문자열 표시
    int no = buffer.toInt();    // 문자열을 정수로 변환

    if (no < 0 || no > 255) {     // 입력한 숫자의 유효성 검사
      Serial.println("잘못된 데이터를 입력했습니다.");
      for (int i = 0; i < 8; i++) {   // 모든 LED를 끔
        digitalWrite(pins[i], LOW);
      }
    }
    else {
      for (int i = 7; i >= 0; i--) {  // LED 제어
        // 비트 연산으로 바이트 단위 패턴값에서 비트 단위 LED 상태 추출
        boolean state = (no >> i) & 1;
        digitalWrite(pins[i], state);

        if (state) {
          Serial.print("O ");   // 켜지는 LED 위치에 ‘O’ 표시
        }
        else {
          Serial.print("X ");   // 꺼지는 LED 위치에 ‘X’ 표시
        }
      }
      Serial.println();
    }

    process_it = false;       // 문자열 처리 완료
    buffer = "";        // 버퍼 비우기
  }
}
