#include <SoftwareSerial.h>

SoftwareSerial SSerial(2, 3);     // (RX, TX)
int pinsLED[] = {4, 5, 6, 7, 8, 9, 10, 11 };

void setup() {
  Serial.begin(9600);
  SSerial.begin(9600);      // 마스터와의 연결
  for (int i = 0; i < 8; i++) {
    pinMode(pinsLED[i], OUTPUT);
    digitalWrite(pinsLED[i], LOW);
  }
}

void loop() {
  if (SSerial.available()) {
    byte data = SSerial.read();

    Serial.println(String("* 수신 데이터 : ") + (int)data);
    Serial.print(" => ");
    for (int i = 7; i >= 0; i--) {
      boolean onoff = (data >> i) & 0x01;
      digitalWrite(pinsLED[i], onoff);
      Serial.print(onoff ? "O " : ". ");
    }
    Serial.println();
  }
}
