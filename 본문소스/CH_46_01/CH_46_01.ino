#include <Servo.h>
#define INTERVAL  5

Servo microServo;     // 서보 모터 제어 객체
int servoPin = 9;       // 서보 모터 연결 핀
int angle = 0, angleStep = 1;   // 현재 회전 위치 및 위치 변화량

void setup() {
  microServo.attach(servoPin);    // 서보 모터 연결
  microServo.write(angle);
}

void loop() {
  angle += angleStep;     // 위치 증감

  if (angle == 180) {     // 180도에 도달하면
    angleStep = -1;     // 각도 감소로 설정
  }
  else if (angle == 0) {      // 0도에 도달하면
    angleStep = 1;      // 각도 증가로 설정
  }

  microServo.write(angle);    // 서보 모터 위치 조정
  delay(INTERVAL);
}
