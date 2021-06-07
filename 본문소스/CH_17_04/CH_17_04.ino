const int ledPin =  LED_BUILTIN;    // LED 연결 핀
boolean ledState = LOW;     // LED 상태
unsigned long count = 0;      // loop 함수 실행 횟수

unsigned long time_previous = 0;    // LED를 반전시킨 시간
const long interval = 1000;   // LED 점멸 간격

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화
  pinMode(ledPin, OUTPUT);    // LED 연결 핀을 출력으로 설정
}

void loop() {
  unsigned long time_current = millis();  // 현재까지의 실행 시간
  count++;            // loop 함수 실행 횟수 증가

  // LED를 반전시킨 이전 시간 이후 1초 이상 시간이 지난 경우
  if (time_current - time_previous >= interval) {
    time_previous = time_current; // LED를 마지막으로 반전시킨 시간

    Serial.print("1초 동안 loop 함수는 ");
    Serial.println(String(count) + "번 실행되었습니다.");
    count = 0;        // loop 함수 실행 횟수 초기화

    ledState = !ledState;     // LED 상태 반전
    digitalWrite(ledPin, ledState);   // LED 상태 출력
  }
}
