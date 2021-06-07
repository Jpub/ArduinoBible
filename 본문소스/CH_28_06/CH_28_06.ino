int selectPin = 2;      // 채널 선택 핀

void setup() {
  Serial.begin(9600);

  pinMode(selectPin, OUTPUT);
}

void loop() {
  digitalWrite(selectPin, LOW);     // 0번 채널
  int v0 = analogRead(A0);

  digitalWrite(selectPin, HIGH);    // 1번 채널
  int v1 = analogRead(A0);

  Serial.println(v0 + String('\t') + v1); // 시리얼로 출력
  delay(100);
}
