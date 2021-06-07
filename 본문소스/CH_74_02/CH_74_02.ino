void setup() {
  Serial.begin(9600);       // 시리얼 포트 3번 초기화
  Serial1.begin(9600);      // 시리얼 포트 1번 초기화
}

void loop() {
  if (Serial.available()) {       // 시리얼 포트 3번의 입력을
    Serial1.write(Serial.read());     // 시리얼 포트 1번으로 출력
  }

  if (Serial1.available()) {    // 시리얼 포트 1번의 입력을
    Serial.write(Serial1.read());   // 시리어 포트 0번으로 출력
  }
}
