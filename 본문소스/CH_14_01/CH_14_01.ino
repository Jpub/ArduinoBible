int pin_vr = A0;       // 가변저항 연결 핀

void setup() {
  Serial.begin(9600);       // 시리얼 통신 초기화
}

void loop() {
  int value = analogRead(pin_vr);   // 가변저항 읽기

  Serial.println(String("현재 가변저항의 값은 ") + value + "입니다.");

  delay(1000);        // 1초 대기
}
