#include <Servo.h>
#define STEP     30    // 속도 변화량
#define MIN_SPEED   0   // 속도 최솟값
#define MAX_SPEED   180   // 속도 최댓값
#define STOP_SPEED  90    // 정지 시 속도 값

Servo continuousServo;      // 서보 모터 제어 객체
int servoPin = 9;       // 서보 모터 연결 핀
int speed = 90;         // 정지 상태

void setup() {
  continuousServo.attach(servoPin);   // 서보 모터 연결
  continuousServo.write(speed);   // 초기 정지 상태로 설정
  delay(20);

  Serial.begin(9600);
  Serial.println("* 정지 상태에서 시작합니다.");
}

void loop() {
  if (Serial.available()) {     // 시리얼 모니터로 데이터 수신
    char ch = Serial.read();

    if (ch == '<') {      // 속도 감소 방향
      speed -= STEP;

      if (speed < MIN_SPEED) {    // 역방향 최대 속도를 넘어간 경우
        speed = MIN_SPEED;
      }
      continuousServo.write(speed); // 속도 변경
      Serial.println(String("* 현재 속도는 ") + speed + "입니다.");
    }
    else if (ch == '>') {     // 속도 증가 방향
      speed += STEP;
      if (speed > MAX_SPEED) {    // 정방향 최대 속도를 넘어간 경우
        speed = MAX_SPEED;
      }
      continuousServo.write(speed); // 속도 변경
      Serial.println(String("* 현재 속도는 ") + speed + "입니다.");
    }
    else if (ch == 's' || ch == 'S') {  // 정지
      speed = STOP_SPEED;
      continuousServo.write(speed);
      Serial.println(String("* 정지하였습니다."));
    }
  }
}
