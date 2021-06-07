#include <Keypad.h>

byte rowPins[4] = { 9, 8, 7, 6 };     // 행 연결 핀
byte colPins[4] = { 5, 4, 3, 2 };     // 열 연결 핀

const byte ROWS = 4;      // 행 수
const byte COLS = 4;      // 열 수

char key_values[] = {       // 키값
  '1', '2', '3', 'A', '4', '5', '6', 'B',
  '7', '8', '9', 'C', '*', '0', '#', 'D'
};

// 키패드 객체 생성 (키값, 행 연결 핀, 열 연결 핀, 행 수, 열 수)
Keypad keypad = Keypad( key_values, rowPins, colPins, ROWS, COLS);

String password = "1234";     // 미리 설정된 비밀번호
String buffer = "";       // 키 입력 버퍼

void setup() {
  Serial.begin(9600);
  Serial.println("** 4자리 비밀번호를 누르세요.");
  Serial.println(" [ 입력 시작 \'*\' 버튼, 입력 종료 \'#\' 버튼 ]");
}

void loop() {
  char key = keypad.getKey();     // 눌러진 키 확인

  if (key) {
    Serial.println(String("=> \'") + key + "\' 버튼을 눌렀습니다.");

    if (key == '#') {       // 비밀번호 입력 종료
      check_input();      // 입력한 비밀번호 검사
      buffer = "";      // 버퍼 비움
      Serial.println("** 4자리 비밀번호를 누르세요.");
      Serial.println(" [ 입력 시작 \'*\' 버튼, 입력 종료 \'#\' 버튼 ]");
    }
    else {
      buffer += key;      // 버퍼에 저장
    }
  }
}

int check_input() {
  int N = buffer.length();      // 마지막 ‘#’를 제외한 입력한 버튼 수

  if (buffer[0] != '*') {
    Serial.println("* 오류 1 : \'*' 버튼부터 눌러야 합니다.");
    return -1;
  }
  if (N != 5) { // 시작 버튼 + 4자리 숫자
    Serial.println("* 오류 2 : 비밀번호는 4자리입니다.");
    return -2;
  }
  for (int i = 1; i < 5; i++) {
    if (buffer[i] < '0' || buffer[i] > '9') {
      Serial.println("* 오류 3 : 비밀번호는 숫자로만 이루어져 있습니다.");
      return -3;
    }
  }
  if (!buffer.substring(1).equals(password)) {
    Serial.println("* 오류 4 : 비밀번호가 맞지 않습니다.");
    return -4;
  }

  Serial.println("* 비밀번호를 정확하게 눌렀습니다.");
  return 1;
}
