char TERMINATOR = '\n';     // 종료 문자
String buffer = "";       // 문자열 수신 버퍼
boolean process = false;      // 문자열 처리 시점 알림

void setup() {
  Serial.begin(9600);     // 시리얼 포트 초기화
}

void loop() {
  if (process) {        // 문자열 수신이 종료됨
    process = false;
    Serial.print(buffer + " => ");    // 원본 문자열 출력

    int n = buffer.length();    // 문자열의 길이
    for (int i = n - 1; i >= 0; i--) {  // 원본 문자열을 역순으로 출력
      Serial.print(buffer[i]);
    }
    Serial.println();       // 줄바꿈
    buffer = "";        // 문자열 수신 버퍼 비움
  }
}

// 수신 버퍼에 수신된 데이터가 존재하면 자동으로 호출됨
void serialEvent() {
  char ch = Serial.read();    // 바이트 단위로 읽기

  if (ch == TERMINATOR) {   // 문자열 종료 문자인 경우
    process = true;     // 문자열 수신 종료 표시
  }
  else {              // 문자열 종료 문자가 아닌 경우
    buffer += ch;     // 버퍼에 저장
  }
}
