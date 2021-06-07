#define DEBUG        // 디버깅을 위해 선택한 숫자 출력 지시

int N;              // 아두이노가 선택한 숫자
char TERMINATOR = '\n';   // 문자열 종료 문자
String buffer = "";     // 문자열 저장 버퍼
boolean process_it = false;   // 문자열 처리 여부
int count = 0;        // 숫자 맞추기를 시도한 횟수

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A0));   // 의사 난수 생성기 초기화
  N = random(1, 101);     // 1~100 사이 숫자 선택

#ifdef DEBUG
  Serial.println(String("[DEBUG] 선택한 숫자는 ") + N + "입니다.");
#endif
  Serial.println("* 1과 100 사이의 숫자를 입력하세요.");
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
    int input_number = buffer.toInt();  // 문자열을 숫자로 변환
    count++;          // 숫자 맞추기를 시도한 횟수 증가

    Serial.print(" => 입력한 숫자 ");
    Serial.print(input_number);
    Serial.print("은/는 생각하고 있는 숫자");

    // 아두이노가 선택한 숫자와 사용자가 입력한 숫자를 비교하여 메시지 출력
    if (input_number > N) {
      Serial.println("보다 큽니다.");
    }
    else if (input_number < N) {
      Serial.println("보다 작습니다.");
    }
    else {
      Serial.println("와 같습니다.");
      Serial.println(String(" => ") + count + "번 시도로 숫자를 찾았습니다.");
      Serial.println(" => 게임을 끝냅니다.");
      while (true);     // 한 번 실행 후 멈춤
    }
    Serial.println("* 1과 100 사이의 숫자를 입력하세요.");

    process_it = false;     // 문자열 처리 완료
    buffer = "";        // 버퍼 비우기
  }
}
