void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화, 9600 보율
}

void loop() {
  while (Serial.available()) {    // 컴퓨터에서 전송한 데이터가 있는 경우
    char ch = Serial.read();    // 데이터를 읽음
    Serial.write(ch);     // 컴퓨터로 같은 내용을 전송
  }
}
