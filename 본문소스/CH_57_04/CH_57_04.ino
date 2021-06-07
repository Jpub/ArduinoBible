#include <Adafruit_SleepyDog.h>

int count = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("* 슬립 모드 데모를 시작합니다.");
  Serial.println();
}

void loop() {
  Serial.println("* 4초 동안 슬립 모드로 들어갑니다.");
  delay(50);

  // 슬립 모드 지속 시간 동안 슬립 모드로 전환한다. 슬립 모드 지속 시간은
  // 표 57.1에서 지정한 시간과 같거나 짧은 시간 중 가장 긴 시간이 선택된다.
  int actual_sleep_time = Watchdog.sleep(4500);

  // 와치독 타이머가 만료되면 여기서부터 다시 시작한다.
  delay(50);
  Serial.print(String("* ") + actual_sleep_time);
  Serial.println("ms 동안 슬립 모드에 있었습니다.");
  Serial.println();
}
