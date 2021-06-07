#include <NewPing.h>

#define TRIGGER_PIN     3
#define ECHO_PIN    2
#define MAX_DISTANCE    200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned int pingSpeed = 500;   // 0.5초 간격으로 거리 측정
unsigned long pingTimer;  // 거리 측정 시간 결정

void setup() {
  Serial.begin(9600);
  pingTimer = millis();
}

void loop() {
  if (millis() >= pingTimer) {  // 거리를 측정할 시간이 지난 경우
    pingTimer += pingSpeed;   // 다음 거리 측정 시간 설정
    // 24마이크로초마다 echoCheck 함수를 호출하도록 Timer2 설정
    sonar.ping_timer(echoCheck);
  }
}

void echoCheck() {
  if (sonar.check_timer()) {  // 에코 핀의 펄스 입력 종료 검사
    Serial.print("전방 장애물까지 거리 = ");
    // 마이크로초 단위의 펄스 길이를 cm 단위 거리로 변환
    Serial.print(sonar.convert_cm(sonar.ping_result));
    Serial.println(" cm");
  }
}
