#include <MobaTools.h>

MoToServo microServo;       // 서보 모터 제어 객체
int servoPin = 9;       // 서보 모터 연결 핀
int rotate = -1;        // 회전 방향

unsigned long time_previous;

void setup() {
  Serial.begin(9600);

  microServo.attach(servoPin);    // 서보 모터 연결

  microServo.setSpeed(0);
  microServo.write(0);      // 0도 위치에서 시작
  delay(200);

  time_previous = millis();
}

void loop() {
  unsigned long time_current = millis();
  if (time_current - time_previous >= 1000) {
    time_previous = time_current;
    Serial.print('.');      // 1초에 한 번 도트 출력
  }
  if (microServo.moving() == 0) {   // 회전하지 않을 때
    if (rotate == -1) {       // 180 -> 0
      rotate = 1;       // 0 -> 180
      microServo.setSpeed(10);    // 4초에 180도 회전
      microServo.write(180);

      Serial.println("\t정회전으로 바꿈");
    }
    else if (rotate == 1) {     // 0 -> 180
      rotate = -1;      // 180 -> 0
      microServo.setSpeed(32);    // 2초에 180도 회전
      microServo.write(0);

      Serial.println("\t역회전으로 바꿈");
    }
  }
}
