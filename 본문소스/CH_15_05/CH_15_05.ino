char TERMINATOR = '\n';     // 문자열 종료 문자
String buffer = "";       // 문자열 저장 버퍼
boolean process_it = false;     // 문자열 처리 여부
int RGB_LED[] = {11, 10, 9};    // (R, G, B) RGB LED 연결 핀

void setup() {
  Serial.begin(9600);
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
    int index_start = 0, index_current = -1;
    byte brightness[3] = {0}, index_rgb = 0;  // RGB 값 분리 저장

    Serial.print("( ");
    while (true) {
      // 문자열 내에서 콤마(‘,’) 위치 탐색
      index_current = buffer.indexOf(',', index_current + 1);
      if (index_current != -1) {    // 콤마 발견
        String str = buffer.substring(index_start, index_current);
        str.trim();     // 앞뒤 공백 제거

        Serial.print(str + " , ");

        brightness[index_rgb] = str.toInt();  // R과 G 값을 배열에 저장
        index_rgb++;

        index_start = index_current + 1;  // 콤마 탐색 시작 위치 조정
      }
      else {          // 마지막 B 값으로 더 이상 콤마 없음
        String str = buffer.substring(index_start);
        str.trim();

        Serial.println(str + " )");

        brightness[index_rgb] = str.toInt();  // B 값을 배열에 저장

        break;
      }
    }

    for (int i = 0; i < 3; i++) {   // 공통 양극 방식을 고려한 출력
      analogWrite(RGB_LED[i], 255 - brightness[i]);
    }

    process_it = false;       // 문자열 처리 완료
    buffer = "";        // 버퍼 비우기
  }
}
