#include <Adafruit_SleepyDog.h>

int count = 0;

void setup() {
  // 와치독 타이머를 설정한다. 와치독 타이머 만료 시간은 표 57.1에서
  // 지정한 시간과 같거나 짧은 시간 중 가장 긴 시간이 선택된다.
  int expire_time = Watchdog.enable(4500);

  Serial.begin(9600);
  Serial.print("* 와치독 타이머 만료 시간은 ");
  Serial.println(String(expire_time) + "ms 입니다.");
}

void loop() {
  delay(1000);
  count++;
  Serial.println(String(" => ") + count + "초가 경과했습니다.");

  // 와치독 타이머 리셋, 와치독 타이머 시간을 0으로 되돌림
  // Watchdog.reset();
}
