#include <avr/sleep.h>
#define interruptPin 2

void setup() {
  Serial.begin(9600);

  pinMode(interruptPin, INPUT_PULLUP);  // 내부 풀업 저항 사용
}

void loop() {
  Serial.println("* 5초 후에 슬립 모드에 들어갑니다.");
  for (byte i = 0; i < 5; i++) {
    delay(1000);
    Serial.print(" => 슬립 모드 진입 ");
    Serial.print(4 - i);
    Serial.println(" 초 전...");
  }
  Serial.println("* 슬립 모드에 들어갑니다.");
  Serial.println(" => 버튼을 누르면 슬립 모드에서 깨어납니다.");
  delay(100);         // 시리얼 출력 완료 대기

  goToSleep();        // 슬립 모드 시작
}

void goToSleep() {
  // 슬립 모드에서 깨어날 수 있도록 인터럽트 설정
  attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUp, LOW);

  // ① 파워 다운 모드 설정
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();       // ② 슬립 모드 활성화
  sleep_cpu();        // ③ 슬립 모드 진입

  // 슬립 모드에서 깨어나면 여기서부터 실행되지만
  // 인터럽트에 의해 깨어나므로 ISR이 먼저 실행된다.
  Serial.println(" => 슬립 모드에서 깨어났습니다.");
  Serial.println();
}

void wakeUp() {
  sleep_disable();      // ④ 슬립 모드 비활성화
  Serial.println("* 인터럽트가 발생해서 슬립 모드에서 깨어납니다.");
  detachInterrupt(digitalPinToInterrupt(interruptPin));   // 인터럽트 제거
}
