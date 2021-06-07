#include <PlayRtttl.h>

const int TONE_PIN = 8, LED_PIN = 13;
unsigned long time_previous;
bool LEDstate = false;
int INTERVAL = 2000;      // LED 점멸 간격

char myMusic[] = "SchoolBell:d=4,o=6,b=200:g,g,a,a,g,g,2e,g,g,e,e,2d.,p,g,g,a,a,g,g,2e,g,e,d,e,2c.,p";

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);   // LED 연결 핀을 출력으로 설정
  digitalWrite(LED_PIN, LEDstate);

  time_previous = millis();

  Serial.println("** 배경음악 재생을 시작합니다.");
  startPlayRtttl(TONE_PIN, myMusic);  // 배경 음악 재생 시작
}

void loop() {
  unsigned long time_current = millis();

  // 지정한 시간이 지나면 LED 상태를 반전
  if (time_current - time_previous >= INTERVAL) {
    time_previous = time_current;
    LEDstate = !LEDstate;
    digitalWrite(LED_PIN, LEDstate);

    Serial.print("* LED 상태가 ");
    Serial.print(LEDstate ? "ON으로 " : "OFF로 ");
    Serial.println("바뀌었습니다.");
  }

  // 재생 상태를 업데이트하고 재생이 끝나면 다시 재생 시작
  if (!updatePlayRtttl()) {
    startPlayRtttl(TONE_PIN, myMusic);
    Serial.println("** 배경음악 재생을 다시 시작합니다.");
  }
}
