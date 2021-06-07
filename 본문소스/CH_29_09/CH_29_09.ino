int dustPin = A0;       // 먼지 센서 출력 핀
int ledPin = 9;         // 적외선 LED 제어 핀

float rawRead = 0;      // 아날로그 입력값
float calcVoltage = 0;      // 전압으로 변환한 값
float dustDensity = 0;      // 먼지 농도

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  digitalWrite(ledPin, LOW);    // 적외선 LED 켜기
  delayMicroseconds(280);   // 280us 이후 먼지 센서 읽음

  rawRead = analogRead(dustPin);  // 먼지 센서 읽기

  delayMicroseconds(40);      // 280 + 40 = 320us 이후 적외선 LED 끔
  digitalWrite(ledPin, HIGH);     // 적외선 LED 끄기
  delayMicroseconds(9680);    // 최소 10ms 간격 유지

  calcVoltage = rawRead * (5.0 / 1024.0); // 전압으로 변환
  dustDensity = 0.17 * calcVoltage - 0.1; // 먼지 농도로 변환

  Serial.print("아날로그 입력 : ");
  Serial.print(rawRead);
  Serial.print("\t전압 : ");
  Serial.print(calcVoltage);
  Serial.print("\t먼지 농도 : ");
  Serial.println(dustDensity);

  delay(1000);        // 1초 간격으로 측정해서 출력
}
