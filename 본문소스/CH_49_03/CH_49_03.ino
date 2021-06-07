#include <PlayRtttl.h>

const int TONE_PIN = 8, LED_PIN = 13;
unsigned long time_previous;
bool LEDstate = false;
int INTERVAL = 2000;      // LED 점멸 간격

char myMusic[] =
  "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,"
  "4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,"
  "p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";

void setup() {
  pinMode(LED_PIN, OUTPUT);   // LED 연결 핀을 출력으로 설정
  digitalWrite(LED_PIN, LEDstate);

  time_previous = millis();

  // 배경음악 재생 시작, 재생이 종료되면 콜백 함수 자동 호출
  startPlayMusic();
}

void startPlayMusic() {     // 재생이 끝났을 때 호출되는 콜백 함수
  startPlayRtttl(TONE_PIN, myMusic, startPlayMusic);
}

void loop() {
  unsigned long time_current = millis();

  // 지정한 시간이 지나면 LED 상태를 반전
  if (time_current - time_previous >= INTERVAL) {
    time_previous = time_current;
    LEDstate = !LEDstate;
    digitalWrite(LED_PIN, LEDstate);
  }

  updatePlayRtttl();      // 재생 상태 업데이트
}
