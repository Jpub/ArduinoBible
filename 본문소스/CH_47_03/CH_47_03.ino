#include <Unistep2.h>

#define STEPS_PER_REV   4096  // 1회전을 위한 스텝 수
#define INTERVAL    1000  // LED 점멸 간격

int pinLED = 13;        // LED 연결 핀
boolean stateLED = false;   // LED 상태

// (IN1, IN2, IN3, IN4, 1회전을 위한 스텝 수, 스텝 사이의 지연 시간(us))
Unistep2 stepper(8, 9, 10, 11, STEPS_PER_REV, 900);
int direction = 1;      // 스텝 모터 회전 방향
unsigned long time_previous;

void setup() {
  pinMode(pinLED, OUTPUT);    // LED 연결 핀을 출력으로 설정
  digitalWrite(pinLED, stateLED);

  Serial.begin(9600);

  time_previous = millis();
}

void loop() {
  unsigned long time_current = millis();
  // INTERVAL 시간 간격을 LED 상태를 반전시켜 LED에 출력
  if (time_current - time_previous >= INTERVAL) {
    time_previous = time_current;
    stateLED = !stateLED;
    digitalWrite(pinLED, stateLED);

    Serial.print("* LED의 상태가 ");
    Serial.print(stateLED ? "ON " : "OFF ");
    Serial.println("상태로 바뀌었습니다.");
  }

  stepper.run();        // 폴링 방식의 스텝 모터 상태 갱신

  if (stepper.stepsToGo() == 0) {   // 이전에 지정한 회전이 끝난 경우
    direction *= -1;      // 회전 방향을 반대로 설정
    stepper.move(STEPS_PER_REV * direction);
    Serial.println("** 스텝 모터가 회전 방향을 바꾸었습니다.");
  }
}
