#include <avr/wdt.h>

int count = 0;

void setup() {
  // 와치독 타이머 설정, 와치독 타이머 만료 시간을 4초로 설정
  wdt_enable(WDTO_4S);

  Serial.begin(9600);
  Serial.println("* 스케치를 시작합니다.");
}

void loop() {
  delay(1000);
  count++;
  Serial.println(String(" => ") + count + "초가 경과했습니다.");

  // 와치독 타이머 리셋, 와치독 타이머 시간을 0으로 되돌림
  // wdt_reset();
}
