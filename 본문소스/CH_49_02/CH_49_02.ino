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
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);   // LED 연결 핀을 출력으로 설정
  digitalWrite(LED_PIN, LEDstate);

  time_previous = millis();

  Serial.println("** 배경음악 재생을 시작합니다.");
  startPlayRtttl(TONE_PIN, myMusic);  // 배경음악 재생 시작
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
