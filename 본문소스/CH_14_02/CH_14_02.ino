int pin_vr = A0;       // 가변저항 연결 핀

void setup() {
  Serial.begin(9600);       // 시리얼 통신 초기화
}

void loop() {
  int value = analogRead(pin_vr);   // 가변저항 읽기

  Serial.println(value);      // 값만 출력

  delay(50);          // 초당 20 샘플 출력
}
