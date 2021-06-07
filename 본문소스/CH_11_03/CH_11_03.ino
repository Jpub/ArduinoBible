#define DEBUG         // 디버깅을 위해 선택한 숫자 출력 지시

String N;             // 아두이노가 선택한 세 자리 숫자
char TERMINATOR = '\n';     // 문자열 종료 문자
String buffer = "";       // 문자열 저장 버퍼
boolean process_it = false;     // 문자열 처리 여부
int count = 0;        // 숫자 맞추기를 시도한 횟수

void setup() {
  Serial.begin(9600);
  make_3_digit_number();    // 3자리 숫자 정하기

#ifdef DEBUG
  Serial.println("[DEBUG] 선택한 숫자는 " + N + "입니다.");
#endif
  Serial.println("* 3자리 정수를 입력하세요.");
}

void make_3_digit_number() {    // 중복 없이 9개 중 3개 숫자 선택
  int n[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  randomSeed(analogRead(A0));     // 의사 난수 생성기 초기화
  for (int i = 0; i < 200; i++) {   // 배열 내 숫자 위치를 200회 자리바꿈
    int index1 = random(9), index2 = random(9);

    int temp = n[index1];
    n[index1] = n[index2];
    n[index2] = temp;
  }
  N = String(n[0]) + n[1] + n[2];   // 3자리 숫자를 문자열로 저장
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
    count++;        // 숫자 맞추기를 시도한 횟수 증가

    // 스트라이크 및 볼 판정
    int strike = 0, ball = 0;
    if (buffer[0] == N[0])  strike++;
    else if (buffer[0] == N[1] || buffer[0] == N[2]) ball++;
    if (buffer[1] == N[1])  strike++;
    else if (buffer[1] == N[0] || buffer[1] == N[2]) ball++;
    if (buffer[2] == N[2]) strike++;
    else if (buffer[2] == N[0] || buffer[2] == N[1]) ball++;

    Serial.print(" => 입력한 숫자 " + buffer + " : ");
    Serial.println(String(strike) + " 스트라이크, " + ball + " 볼");

    if (strike == 3) {
      Serial.println(String(" => ") + count + "번 시도로 숫자를 찾았습니다.");
      Serial.println(" => 게임을 끝냅니다.");
      while (true);       // 한 번 실행 후 멈춤
    }

    Serial.println("* 3자리 정수를 입력하세요.");

    process_it = false;       // 문자열 처리 완료
    buffer = "";        // 버퍼 비우기
  }
}
