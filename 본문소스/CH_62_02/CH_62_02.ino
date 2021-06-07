int main(void) {
  init();             // 아두이노 환경 초기화

  Serial.begin(9600);     // 컴퓨터와의 시리얼 통신 초기화
  int count = 0;        // 카운터 값

  while (1) {
    count++;          // 카운터 값 증가
    Serial.print("* 현재 카운터 값은 ");
    Serial.print(count);
    Serial.println("입니다.");

    delay(1000);        // 1초 대기
  }

  return 1;
}
