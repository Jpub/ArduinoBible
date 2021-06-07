#include <Servo.h>

// 가변저항 값이 1024를 20단계로 나눈 값의 50% 이상 변할 때만 시간 조절
#define THRESH ((1024 / 20) / 2)

Servo microServo;       // 서보 모터 제어 객체
int servoPin = 9;       // 서보 모터 연결 핀

unsigned long time_previous, time_current;
int interval = 10;      // 현재 이동 시간 간격
int reading = -2000;      // 가변저항 값
int angle = 0;        // 현재 회전 위치 및 위치 변화량
int angle_step = 1;       // 회전 위치 변화량 (1 or –1)

void setup() {
  microServo.attach(servoPin);    // 서보 모터 연결
  Serial.begin(9600);

  microServo.write(angle);    // 0도에서 시작
  delay(100);

  time_previous = millis();
}

void loop() {
  time_current = millis();

  if (time_current - time_previous >= interval) {
    time_previous = time_current;

    angle += angle_step;    // 현재 위치 조정
    if (angle >= 180) {       // 180도를 넘어가면 방향 전환
      angle = 180;
      angle_step *= -1;
    }
    else if (angle <= 0) {    // 0도를 넘어가면 방향 전환
      angle = 0;
      angle_step *= -1;
    }

    microServo.write(angle);    // 서보 모터 위치 조정
  }

  int reading_cur = analogRead(A0);   // 가변저항 값 읽기
  // 임계치 이상 변한 경우에만 이동 시간 간격 조정
  if (abs(reading_cur - reading) > THRESH) {
    reading = reading_cur;
    int new_interval = map(reading, 0, 1023, 5, 20);
    if (new_interval != interval) {
      interval = new_interval;    // 이동 시간 간격 조정
      Serial.print("* 회전 위치 증감을 위한 지연 시간 : ");
      Serial.println(interval);
    }
  }
}
