int rowPins[4] = { 9, 8, 7, 6 };    // 행 연결 핀
int colPins[4] = { 5, 4, 3, 2 };    // 열 연결 핀
char key_value[][4] = {     // 각 버튼의 키값
  '1', '2', '3', 'A', '4', '5', '6', 'B',
  '7', '8', '9', 'C', '*', '0', '#', 'D'
};

// 16개 버튼의 상태를 16비트 변수에 저장
uint16_t key_state_previous = 0, key_state_current;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);  // 행 핀은 내부 풀업 저항 사용
    pinMode(colPins[i], INPUT);   // 열 핀은 하이 임피던스 상태로 설정
  }

  Serial.begin(9600);
}

void loop() {
  key_state_current = 0;
  for (int col = 0; col < 4; col++) {
    pinMode(colPins[col], OUTPUT);  // 선택한 열만 출력으로 설정
    digitalWrite(colPins[col], LOW);  // 선택한 열만 LOW 출력

    for (int row = 0; row < 4; row++) {
      // 각 행의 버튼 상태 읽기
      boolean press = !digitalRead(rowPins[row]); // 각 행의 버튼 상태 읽기
      if (press) {        // 16비트 변수에 16개 버튼 상태 저장
        key_state_current |= (1 << (col * 4 + row));
      }
    }
    pinMode(colPins[col], INPUT);   // 선택한 열을 하이 임피던스 상태로 설정
  }

  if (key_state_current != key_state_previous) {  // 버튼을 누른 상태가 바뀐 경우
    key_state_previous = key_state_current;
    if (key_state_current != 0) {   // 버튼을 모두 떼는 경우는 출력하지 않음
      print_key_state(key_state_current);
    }
  }
}

void print_key_state(uint16_t key_state) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      boolean press = (key_state >> (col * 4 + row)) & 1;
      if (press) {        // 눌러진 키는 키값 출력
        Serial.print(String(key_value[row][col]) + ' ');
      }
      else {          // 누르지 않은 키
        Serial.print(". ");
      }
    }
    Serial.println();
  }
  Serial.println();
}
