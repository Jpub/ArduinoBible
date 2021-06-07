void setup() {
  Serial.begin(9600);

  int A = 10;

  if (A == 10) {      // A가 10과 같은지 비교 (비교 연산자)
    Serial.println("A는 10입니다 !!");
  }

  if (A = 5) {      // (대입 연산자)
    // A에 5를 대입하면 A는 0이 아닌 값을 가지므로 논리 참이 되고
    // if 블록의 코드가 실행된다.
    Serial.println("A는 5인가요 ??");
  }
}

void loop() { }
