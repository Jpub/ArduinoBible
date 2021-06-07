#include <LowPower.h>

int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // 8초 동안 파워 다운 모드에 진입
  // LowPower.powerDown(SLEEP_8S, ADC_ON, BOD_ON);
  // LowPower.powerDown(SLEEP_8S, ADC_ON, BOD_OFF);
  // LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_ON);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

  count++;
  Serial.print("* 카운터 값 : ");
  Serial.print(count);

  Serial.print("  ");
  for (byte i = 0; i < 10; i++) {     // 10초 동안 일반 모드 동작
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  delay(100);         // 시리얼 출력 완료 대기
}
