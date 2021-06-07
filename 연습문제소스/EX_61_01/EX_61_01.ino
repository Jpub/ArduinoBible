#include <LowPower.h>

#define interruptPin 2

void setup() {
  Serial.begin(9600);

  pinMode(interruptPin, INPUT_PULLUP);
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
  delay(1000);        // 시리얼 출력 대기

  goToSleep();
}

void goToSleep() {
  attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUp, LOW);

  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  Serial.println(" => 슬립 모드에서 깨어났습니다.");
  Serial.println();
}

void wakeUp() {
  Serial.println("* 인터럽트가 발생해서 슬립 모드에서 깨어납니다.");
  detachInterrupt(digitalPinToInterrupt(interruptPin));
}
