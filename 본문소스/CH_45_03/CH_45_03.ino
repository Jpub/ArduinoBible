int ENABLE_A = 10;       // Enable A 핀
int INPUT_1 = 9;      // 모터 제어 핀 1
int INPUT_2 = 8;      // 모터 제어 핀 2

int BUTTON_PIN = 2;
boolean direction = true;     // 정회전

void setup() {
  pinMode(ENABLE_A, OUTPUT);
  pinMode(INPUT_1, OUTPUT);
  pinMode(INPUT_2, OUTPUT);

  digitalWrite(ENABLE_A, HIGH);     // 최대 속도
  pinMode(BUTTON_PIN, INPUT);     // 버튼 연결 핀을 입력으로 설정

  forward();          // 정회전으로 시작
  Serial.begin(9600);
  Serial.println("* 시작...");
}

void loop() {
  if (digitalRead(BUTTON_PIN)) {
    direction = !direction;     // 버튼이 눌러지면 회전 방향 바꿈

    if (direction) {
      forward();
      Serial.println(" => 앞으로...");
      delay(500);
    }
    else {
      backward();
      Serial.println(" => 뒤로...");
      delay(500);
    }
  }
}

void forward() {
  digitalWrite(INPUT_1, LOW);     // 표 45.3 참고
  digitalWrite(INPUT_2, HIGH);
}

void backward() {
  digitalWrite(INPUT_1, HIGH);    // 표 45.3 참고
  digitalWrite(INPUT_2, LOW);
}
