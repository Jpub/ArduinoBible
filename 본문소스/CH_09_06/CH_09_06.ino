// Level 0 : 스케치 내 어디에서도 사용 가능한 전역 변수
int A = 0;

void setup() {
  Serial.begin(9600);

  // 변수는 사용 이전에 선언되어야 하며
  // 블록 내에 선언된 변수가 없으면 상위 블록에 선언된 변수를 사용
  Serial.println(String("A의 값은 ") + A + "입니다.");

  // Level 1 : setup 함수 내에서만 유효한 지역 변수
  int A = 1;
  Serial.println(String("A의 값은 ") + A + "입니다.");

  if (A == 1) {         // Level 1 변수 사용
    // Level 2 : setup 함수 내의 if 블록 내에서만 유효한 지역 변수
    int A = 2;
    Serial.println(String("A의 값은 ") + A + "입니다.");

    { // 하위 블록을 형성하기 위한 중괄호
      // Level 3 : setup 함수 내, if 블록 내, 중괄호({ }) 블록에서만 유효한 지역 변수
      int A = 3;
      Serial.println(String("A의 값은 ") + A + "입니다.");
    }
  }
}

void loop() { }
