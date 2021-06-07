#include <SoftwareSerial.h>

byte TERMINATOR = 0;

SoftwareSerial SSerial(2, 3);     // (RX, TX)
String buffer = "";

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 연결
  SSerial.begin(9600);      // 슬레이브와의 연결
}

void loop() {
  if (SSerial.available()) {    // 데이터 수신 확인
    byte data = SSerial.read();     // 데이터 읽기

    if (data == TERMINATOR) {     // 문자열의 끝
      Serial.println(String("슬레이브로부터 수신한 값 : ") + buffer.toInt());
      buffer = "";      // 버퍼 비우기
    }
    else {
      buffer += (char)data;     // 버퍼에 저장
    }
  }
}
