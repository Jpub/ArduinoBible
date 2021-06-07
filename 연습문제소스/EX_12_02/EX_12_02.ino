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

  if (process_it) {       // 저장된 문자열을 처리하는 경우
    Serial.print("\'" + buffer + "\' : ");  // 입력 문자열 표시
    int no = buffer.toInt();    // 문자열을 정수로 변환

    if (no < 0 || no > 8) {   // 입력한 숫자의 유효성 검사
      Serial.println("잘못된 숫자를 입력했습니다.");
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], LOW);
      }
    }
    else {
      Serial.println(String(no) + "개 LED를 켭니다.");

      for (int i = 0; i < 8; i++) {   // LED 제어
        if (i < no) {
          digitalWrite(pins[i], HIGH);
        }
        else {
          digitalWrite(pins[i], LOW);
        }
      }
    }

    process_it = false;       // 문자열 처리 완료
    buffer = "";        // 버퍼 비우기
  }
}
