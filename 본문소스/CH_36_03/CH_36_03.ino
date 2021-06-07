#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // (주소, 열, 행)

byte rowPins[4] = { 9, 8, 7, 6 };     // 행 연결 핀
byte colPins[4] = { 5, 4, 3, 2 };     // 열 연결 핀

const byte ROWS = 4;      // 행 수
const byte COLS = 4;      // 열 수

char key_values[] = {       // 키 값
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'
};

// 키 값 ‘A’에서 ‘D’까지를 사칙연산자로 대응시켜 출력
char operatorSymbol[] = { '+', '-', '*', '/' };

// 키패드 객체 생성 (키값, 행 연결 핀, 열 연결 핀, 행 수, 열 수)
Keypad keypad = Keypad( key_values, rowPins, colPins, ROWS, COLS);

byte X = 0;           // 텍스트 LCD에 키 입력을 표시할 위치

byte state = 1;         // 계산기의 상태
int operand1, operand2, result;   // 입력한 숫자와 계산 결과
char op;            // 입력한 사칙연산자

void setup() {
  lcd.init();           // LCD 초기화
  lcd.backlight();      // 백라이트 켜기

  resetCalculator();      // 계산기 초기화
  displayMessage("* Let's Start !");
}

void loop() {
  char key = keypad.getKey();     // 눌러진 키 확인

  if (key) {          // 키가 눌러진 경우
    switch (state) {      // 현재 상태에 따라 다른 함수 호출
      case 1: handleState1(key); break;
      case 2: handleState2(key); break;
      case 3: handleState3(key); break;
      case 4: handleState4(key); break;
    }
  }
}

void resetCalculator() {      // 계산기 상태 초기화
  state = 1;          // 초기 상태
  operand1 = 0;       // 첫 번째 피연산자
  operand2 = 0;       // 두 번째 피연산자
  result = 0;         // 계산 결과
  op = 0;             // 연산자

  lcd.clear();
  X = 0;              // 키 입력 표시 위치
}

void displayInput(char key) {   // 키 입력을 텍스트 LCD에 표시
  lcd.setCursor(X, 0);      // 첫 번째 줄에 표시
  lcd.write(key);

  X = (X + 1) % 16;
}

void displayMessage(char *msg) {    // 메시지 출력
  lcd.setCursor(0, 1);      // 두 번째 줄에 표시
  lcd.print(msg);
}

void handleState1(char key) {     // 상태 1
  if (keyInGroup1(key)) {     // 숫자 키 입력
    resetCalculator();      // 수식 입력 시작에 따른 계산기 초기화

    state = 2;        // 상태 2로 이동
    operand1 = key - '0';   // 첫 번째 피연산자 계산
    displayInput(key);      // 텍스트 LCD에 키 입력 표시
  }
  else if (keyInGroup2(key)) {    // 사칙연산자 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    resetCalculator();      // 계산기 초기화
    displayMessage("* ERR : S1, IN2");  // 오류 : 상태 1에서 그룹 2 키 입력
  }
  else if (keyInGroup3(key)) {    // 등호 연산자 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    resetCalculator();      // 계산기 초기화
    displayMessage("* ERR : S1, IN3");  // 오류 : 상태 1에서 그룹 3 키 입력
  }
  else if (keyInGroup4(key)) {    // 리셋 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    resetCalculator();      // 계산기 초기화
    displayMessage("* RESET");    // 수식 입력 취소로 초기 상태로 이동
  }
}

void handleState2(char key) {     // 상태 2
  if (keyInGroup1(key)) {     // 숫자 키 입력
    operand1 = operand1 * 10 + (key - '0'); // 첫 번째 피연산자 업데이트
    displayInput(key);
  }
  else if (keyInGroup2(key)) {    // 사칙연산자 키 입력
    state = 3;        // 상태 3으로 이동
    op = key;         // 연산자 저장
    displayInput(operatorSymbol[key - 'A']);
  }
  else if (keyInGroup3(key)) {    // 등호 연산자 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    displayMessage("* ERR : S2, IN3");  // 오류 : 상태 2에서 그룹 3 키 입력
  }
  else if (keyInGroup4(key)) {    // 리셋 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    displayMessage("* RESET");    // 수식 입력 취소로 초기 상태로 이동
  }
}

void handleState3(char key) {     // 상태 3
  if (keyInGroup1(key)) {     // 숫자 키 입력
    state = 4;        // 상태 4로 이동
    operand2 = key - '0';   // 두 번째 피연산자 계산
    displayInput(key);
  }
  else if (keyInGroup2(key)) {    // 사칙연산자 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    displayMessage("* ERR : S3, IN2");  // 오류 : 상태 3에서 그룹 2 키 입력
  }
  else if (keyInGroup3(key)) {    // 등호 연산자 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    displayMessage("* ERR : S3, IN3");  // 오류 : 상태 3에서 그룹 3 키 입력
  }
  else if (keyInGroup4(key)) {    // 리셋 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    displayMessage("* RESET");    // 수식 입력 취소로 초기 상태로 이동
  }
}

void handleState4(char key) {     // 상태 4
  if (keyInGroup1(key)) {     // 숫자 키 입력
    operand2 = operand2 * 10 + (key - '0'); // 두 번째 피연산자 업데이트
    displayInput(key);
  }
  else if (keyInGroup2(key)) {    // 사칙연산자 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    displayMessage("* ERR : S4, IN2");  // 오류 : 상태 4에서 그룹 2 키 입력
  }
  else if (keyInGroup3(key)) {    // 등호 연산자 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    calculateResult();      // 계산 결과 표시
  }
  else if (keyInGroup4(key)) {    // 리셋 키 입력
    state = 1;        // 상태 1, 초기 상태로 이동
    displayMessage("* RESET");    // 수식 입력 취소로 초기 상태로 이동
  }
}

void calculateResult() {      // 수식 계산
  if (op == 'D' && operand2 == 0) {
    displayMessage("* DIV by ZERO");  // 0으로 나누기 오류
    return;
  }

  switch (op) {
    case 'A' :        // 더하기
      result = operand1 + operand2;
      break;
    case 'B' :          // 빼기
      result = operand1 - operand2;
      break;
    case 'C' :        // 곱하기
      result = operand1 * operand2;
      break;
    case 'D' :        // 나누기
      result = operand1 / operand2;
      break;
  }

  lcd.setCursor(0, 1);      // 두 번째 줄에 계산 결과 표시
  lcd.print(" = ");
  lcd.print(result);
}

boolean keyInGroup1(char key) {     // Group 1 : 숫자 키
  if (key >= '0' && key <= '9')   return true;
  else            return false;
}

boolean keyInGroup2(char key) {     // Group 2 : 사칙연산자 키
  if (key >= 'A' && key <= 'D')   return true;
  else            return false;
}

boolean keyInGroup3(char key) {     // Group 3 : 대입 연산자 키
  return (key == '#');
}

boolean keyInGroup4(char key) {     // Group 4 : 리셋 키
  return (key == '*');
}
