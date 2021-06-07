int CLK = 2;
int DT = 3;
int SW = 4;

int encoderVal = 0;
int oldA = HIGH, oldB = HIGH;    // 초기 상태, 풀업 저항 사용으로 HIGH

void setup() {
  pinMode (CLK, INPUT);     // 인코더 연결 핀을 입력으로 설정
  pinMode (DT, INPUT);
  pinMode (SW, INPUT);

  Serial.begin(9600);
  Serial.print("인코더 시작\t: ");
  Serial.println(encoderVal);
}

void loop() {
  int change = checkEncoder();    // 인코더 회전 결정

  if (change != 0) {      // 회전이 있는 경우
    if (change == 1) {
      Serial.print("시계방향 회전\t: ");
    }
    else {
      Serial.print("반시계방향 회전\t: ");
    }
    encoderVal = encoderVal + change;
    Serial.println(encoderVal);
  }

  if (digitalRead(SW) == LOW) {   // 스위치를 누른 경우 리셋
    encoderVal = 0;

    Serial.print("인코더 리셋\t: ");
    Serial.println(encoderVal);

    delay(100);       // 디바운싱
  }
}

// 1(시계 방향), -1(반시계 방향), 0(회전 없음) 중 하나의 값을 반환
int checkEncoder(void) {
  int result = 0;
  int newA = digitalRead(CLK);
  int newB = digitalRead(DT);

  if (newA != oldA || newB != oldB) { // 값이 변한 경우
    if (oldA == LOW && newA == HIGH) {  // 상승 에지에서
      // B가 LOW(= 0)이면 시계 방향(result = 1)
      // B가 HIGH(= 1)이면 반시계 방향(result = -1)
      result = -(oldB * 2 - 1);
    }
  }

  oldA = newA;
  oldB = newB;

  return result;
}
