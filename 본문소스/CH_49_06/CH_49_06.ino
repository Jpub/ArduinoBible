int buzzerPin = 8, LED_PIN = 13;
bool LEDstate = false, buzzerState = false;

int BUZZER_INTERVAL = 100;
int BLINK_INTERVAL = 1000;
unsigned long time_pre_blink, time_pre_buzzer;

void setup () {
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);     // 버저 연결 핀을 출력으로 설정
  pinMode(LED_PIN, OUTPUT);     // LED 연결 핀을 출력으로 설정

  time_pre_blink = millis();
  time_pre_buzzer = time_pre_blink;
}

void loop () {
  unsigned long time_current = millis();

  // LED 점멸 제어
  if (time_current - time_pre_blink >= BLINK_INTERVAL) {
    time_pre_blink = time_current;

    LEDstate = !LEDstate;
    digitalWrite(LED_PIN, LEDstate);

    Serial.print("\n* LED 상태가 ");
    Serial.print(LEDstate ? "ON으로 " : "OFF로 ");
    Serial.println("바뀌었습니다.");
  }

  // 액티브 버저 on/off 제어
  if (time_current - time_pre_buzzer >= BUZZER_INTERVAL) {
    time_pre_buzzer = time_current;

    buzzerState = !buzzerState;
    digitalWrite(buzzerPin, buzzerState);

    Serial.print('.');
  }
}
