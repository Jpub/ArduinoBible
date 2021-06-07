#include <Servo.h>
#define INTERVAL   5
#define BUFFER_SIZE   5

Servo microServo;     // 서보 모터 제어 객체
int servoPin = 9;       // 서보 모터 연결 핀

int buffer[BUFFER_SIZE] = { 0, };
byte bufferPosition = 0;

void setup() {
  microServo.attach(servoPin);    // 서보 모터 연결

  for (int i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = analogRead(A0);
  }
}

void loop() {
  buffer[bufferPosition] = analogRead(A0);
  bufferPosition = (bufferPosition + 1) % BUFFER_SIZE;

  int vr = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    vr += buffer[i];
  }
  vr /= BUFFER_SIZE;
  int angle = map(vr, 0, 1023, 0, 180); // 각도로 변환

  microServo.write(angle);    // 서보 모터 위치 조정
  delay(INTERVAL);
}
