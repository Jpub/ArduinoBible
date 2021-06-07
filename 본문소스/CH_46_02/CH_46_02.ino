#include <Servo.h>
#define INTERVAL   5

Servo microServo;     // 서보 모터 제어 객체
int servoPin = 9;       // 서보 모터 연결 핀

void setup() {
  microServo.attach(servoPin);    // 서보 모터 연결
}

void loop() {
  int vr = analogRead(A0);    // 가변저항 읽기
  int angle = map(vr, 0, 1023, 0, 180); // 각도로 변환

  microServo.write(angle);    // 서보 모터 위치 조정
  delay(INTERVAL);
}
