#include <SoftwareSerial.h>

SoftwareSerial SSerial(2, 3);     // (RX, TX)
String buffer = "";

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 연결
  SSerial.begin(9600);      // 슬레이브와의 연결
}

void loop() {
  if (Serial.available()) {
    byte data = Serial.read();

    if (data == '\n') {
      Serial.println(String("* 입력한 데이터 : ") + buffer);
      int n = buffer.toInt();
      if (n >= 0 && n <= 255) {
        Serial.println(" => 슬레이브로 데이터를 전송합니다.");
        SSerial.write(n);
        buffer = "";
      }
      else {
        Serial.println(" => 잘못된 값이 입력되었습니다.");
      }
    }
    else {
      buffer += (char)data;
    }
  }
}
