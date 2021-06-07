int N;              // 아두이노가 선택한 숫자
char TERMINATOR = '\n';   // 문자열 종료 문자
String buffer = "";     // 문자열 저장 버퍼
boolean process_it = false;   // 문자열 처리 여부
int state = 1; // 1 : 숫자 입력 상태, 2 : 다시 하기 입력 상태

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A0));   // 의사 난수 생성기 초기화

  Serial.println("** 진법 변환을 시작합니다.");
  make_random_number();
}

void make_random_number() {
  N = random(1, 101);     // 1~100 사이 숫자 선택

  Serial.print("* 이진수 0b");
  Serial.print(N, BIN);
  Serial.println("에 해당하는 십진수를 입력하세요.");
}

void loop() {
  while (Serial.available() > 0) {    // 데이터 수신
    char ch = Serial.read();    // 데이터 읽기

    if (ch == TERMINATOR) {   // 문자열 종료 문자인 경우
      process_it = true;      // 문자열 처리 지시
    }
    else {            // 이외의 문자인 경우
      buffer = buffer + ch;   // 버퍼에 문자 저장
    }
  }

  if (process_it) {     // 저장된 문자열을 처리하는 경우
    if (state == 1) { // 게임 진행 상태
      int input_number = buffer.toInt();  // 문자열을 숫자로 변환

      Serial.print(" => 이진수 0b");
      Serial.print(N, BIN);
      Serial.println(String("는 십진수로 ") + N + "입니다.");

      if (N == input_number) {
        Serial.println(" => 정답입니다 !!");
      }
      else {
        Serial.println(" => 애석합니다...");
      }

      Serial.println(" => 다시 해볼까요? (y/n)");
      state = 2;

      process_it = false;     // 문자열 처리 완료
      buffer = "";        // 버퍼 비우기
    }
    else if (state == 2) {
      if (buffer.equalsIgnoreCase("y")) {
        Serial.println("** 다시 해보겠습니다.");
        make_random_number();

        state = 1;
      }
      else {
        Serial.println("** 진법 변환을 종료합니다.");
        while (1);
      }

      process_it = false;
      buffer = "";
    }
  }
}
