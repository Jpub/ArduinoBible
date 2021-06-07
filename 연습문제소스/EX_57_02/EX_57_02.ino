#include <avr/wdt.h>

int count = 0;
unsigned long time_previous, time_current;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  time_previous = millis();
}

void loop() {
  time_current = millis();
  if (time_current - time_previous >= 1000) {
    count++;
    Serial.println(String("* 현재 카운터 값 : ") + count);
    time_previous = time_current;
  }

  if (digitalRead(2)) {     // 버튼을 누른 경우
    Serial.println("** 버튼을 눌렀으므로 아두이노를 리셋합니다.");
    wdt_enable(WDTO_1S);    // 1초 후 리셋
    while (1);        // 리셋될 때까지 대기
  }
}
