#include <NewPing.h>

const int THRESH1 = 30;     // 1차 근접 기준
const int THRESH2 = 15;     // 2차 근접 기준

// 0 : 충돌 위험 없음, 1 : 충돌 주의(< THRESH1), 2 : 충돌 직전(< THRESH2)
byte state = 0;

NewPing ultrasonic(3, 2);     // (트리거 핀, 에코 핀)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int distanceCM = ultrasonic.convert_cm(ultrasonic.ping_median());

  if (distanceCM <= THRESH2) {
    if (state == 1) {       // 충돌 직전 거리로 진입
      Serial.print(String(distanceCM) + "\t");
      Serial.println("* 곧 충돌합니다!!");
      state = 2;
    }
  }
  else if (distanceCM <= THRESH1) {
    if (state != 1) {     // 충돌 주의 거리로 이동
      Serial.print(String(distanceCM) + "\t");
      Serial.println("* 충돌 위험이 있으니 주의하세요.");
      state = 1;
    }
  }
  else {
    if (state != 0) {       // 충돌 위험 없는 거리로 벗어남
      Serial.print(String(distanceCM) + "\t");
      Serial.println("* 총돌 위험 지역에서 벗어났습니다.");
      state = 0;
    }
  }
}
