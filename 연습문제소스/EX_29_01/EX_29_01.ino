// 0: 조도 일정값 이상, 1: 조도 일정값 미만, LED 켜짐, 2: 조도 일정값 이상, LED 꺼짐
int state = 0;
int state_interval = 1000; // LED 점멸 간격
unsigned long t_previous = 0;
const int THRESH = 500; // 실험적으로 결정한다.

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.println("* 상태 0 : 초기 상태");
}

void loop() {
  int reading = analogRead(A1);

  if (reading < THRESH) { // 조도가 일정 수준 미만
    if (state == 0) { // 조도가 일정 수준 이상에서 떨어질 때
      state = 1;  // 상태 1로 변화
      digitalWrite(13, HIGH);
      Serial.println("* 상태 1 : 조도가 일정 수준 미만 (LED ON)");
    }
  }
  else { // 조도가 일정 수준 이상
    if (state != 0) {
      state = 0;
      digitalWrite(13, LOW);
      Serial.println("* 상태 0 : 조도가 일정 수준 이상");
    }
  }

  unsigned long t_current = millis();
  if (state > 0) {
    if (t_current - t_previous >= state_interval) {
      state = (state == 1) ? 2 : 1;
      switch (state) {
        case 1:
          digitalWrite(13, HIGH);
          Serial.println("* 상태 1 : 조도가 일정 수준 미만 (LED ON)");
          break;
        case 2:
          digitalWrite(13, LOW);
          Serial.println("* 상태 2 : 조도가 일정 수준 미만 (LED OFF)");
          break;
      }
      t_previous = t_current;
    }
  }
  else {
    t_previous = t_current;
  }
}
