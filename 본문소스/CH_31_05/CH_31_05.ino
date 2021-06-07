#include <NewPing.h>

const int THRESH1 = 30;     // 1차 근접 기준
const int THRESH2 = 15;     // 2차 근접 기준

// 0 : 충돌 위험 없음, 1 : 충돌 주의(< THRESH1), 2 : 충돌 직전(< THRESH2)
byte state = 0;

unsigned long time_previous, time_current;  // 상태 2에서 LED 점멸 제어
const int INTERVAL = 200;     // LED 점멸 간격
boolean LED_state;

NewPing ultrasonic(3, 2);     // (트리거 핀, 에코 핀)

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  int distanceCM = ultrasonic.convert_cm(ultrasonic.ping_median());

  if (distanceCM <= THRESH2) {
    if (state == 1) {       // 충돌 직전 거리로 진입
      Serial.print(String(distanceCM) + "\t");
      Serial.println("* 곧 충돌합니다!!");
      state = 2;

      LED_state = HIGH;     // LED 상태 설정
      digitalWrite(13, LED_state);
      time_previous = millis();   // 마지막으로 상태가 바뀐 시간
    }
  }
  else if (distanceCM <= THRESH1) {
    if (state != 1) { // 충돌 주의 거리로 이동
      Serial.print(String(distanceCM) + "\t");
      Serial.println("* 충돌 위험이 있으니 주의하세요.");
      state = 1;

      digitalWrite(13, HIGH);   // LED 켜기
    }
  }
  else {
    if (state != 0) {       // 충돌 위험 없는 거리로 벗어남
      Serial.print(String(distanceCM) + "\t");
      Serial.println("* 총돌 위험 지역에서 벗어났습니다.");
      state = 0;

      digitalWrite(13, LOW);    // LED 끄기
    }
  }

  time_current = millis();
  // 상태 2, 즉, 아주 가까운 거리에 물체가 있을 때 점멸
  if (time_current - time_previous >= INTERVAL && state == 2) {
    LED_state = !LED_state;
    digitalWrite(13, LED_state);

    time_previous = time_current;
  }
}
