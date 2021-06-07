int count = 0;        // 전역 카운터 변수

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화, 9600 보율
}

void loop() {
  plus_two();         // 전역 카운터 변수 2 증가
  Serial.println(count);      // 전역 카운터 변숫값 출력
  delay(1000);        // 1초 대기

  minus_one();        // 전역 카운터 변수 1 감소
  Serial.println(count);      // 전역 카운터 변숫값 출력
  delay(1000);        // 1초 대기
}

void plus_two() {
  count += 2;       // 전역 카운터 변수 2 증가
}

void minus_one() {
  count -= 1;       // 전역 카운터 변수 1 감소
}
