int ENABLE_A = 10;       // Enable A 핀
int INPUT_1 = 9;      // 모터 제어 핀 1
int INPUT_2 = 8;      // 모터 제어 핀 2

void setup() {
  pinMode(ENABLE_A, OUTPUT);
  pinMode(INPUT_1, OUTPUT);
  pinMode(INPUT_2, OUTPUT);

  digitalWrite(ENABLE_A, LOW);    // 제어 불가능한 상태로 둠
}

void loop() {
  forward();          // 정회전
  for (int i = 0; i < 256; i++) {     // Enable 핀으로 속도 증가
    analogWrite(ENABLE_A, i);
    delay(30);
  }

  motor_stop();         // 표 45.3 참고

  backward();         // 역회전
  for (int i = 0; i < 256; i++) {     // 속도 증가
    analogWrite(ENABLE_A, i);
    delay(30);
  }
}

void motor_stop() {
  digitalWrite(INPUT_1, LOW);
  digitalWrite(INPUT_2, LOW);
}

void forward() {
  digitalWrite(INPUT_1, LOW);     // 표 45.3 참고
  digitalWrite(INPUT_2, HIGH);
}

void backward() {
  digitalWrite(INPUT_1, HIGH);    // 표 45.3 참고
  digitalWrite(INPUT_2, LOW);
}
