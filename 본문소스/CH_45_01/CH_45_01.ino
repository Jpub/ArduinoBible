int ENABLE_A = 10;       // Enable A 핀
int INPUT_1 = 9;        // 모터 제어 핀 1
int INPUT_2 = 8;        // 모터 제어 핀 2

void setup() {
  pinMode(ENABLE_A, OUTPUT);
  pinMode(INPUT_1, OUTPUT);
  pinMode(INPUT_2, OUTPUT);

  digitalWrite(ENABLE_A, HIGH);     // 제어 가능한 상태로 둠
}

void loop() {
  forward();          // 정회전
  delay(2000);

  backward();         // 역회전
  delay(2000);
}

void forward() {
  digitalWrite(INPUT_1, LOW);     // 표 45.3 참고
  digitalWrite(INPUT_2, HIGH);
}

void backward() {
  digitalWrite(INPUT_1, HIGH);    // 표 45.3 참고
  digitalWrite(INPUT_2, LOW);
}
