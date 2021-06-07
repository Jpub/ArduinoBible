/********************************************
    함수 선언 : 스케치에서 함수 선언은 생략 가능
********************************************/
// float get_result(void);      // 함수 선언 없이 호출 가능
void print_result(float r);
int recursive_sum(int n);

/********************************************
    함수 정의 : 사용자 정의 함수 3개 포함 5개
********************************************/
void setup() {
  Serial.begin(9600);

  float result = get_result();    // 매개변수가 없는 함수
  print_result(result);         // 반환값이 없는 함수

  int sum = recursive_sum(10);    // 재귀 함수
  Serial.println(String("1부터 10까지의 합은 ") + sum + "입니다.");
}

float get_result(void) {
  return sin(30.0 * 3.14 / 180.0);    // 라디안 형식의 각도 지정
}

void print_result(float r) {
  Serial.println(String("싸인 30도 값은 ") + r + "입니다.");
}

int recursive_sum(int n) {
  if (n == 1) {
    return 1;
  }
  else {
    return n + recursive_sum(n - 1);
  }
}

void loop() { }
