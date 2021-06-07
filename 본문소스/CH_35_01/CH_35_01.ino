#include <SoftwareSerial.h>

SoftwareSerial gps(2, 3);      // GPS 리시버 연결 포트 (RX, TX)

void setup() {
  Serial.begin(9600);     // 컴퓨터와의 시리얼 연결
  gps.begin(9600);      // GPS 리시버와의 시리얼 연결
}

void loop() {
  if (gps.available()) {      // GPS 리시버로부터 데이터 수신
    char ch = gps.read();   // GPS 리시버로부터 데이터 읽기
    Serial.write(ch);     // 시리얼 모니터로 출력
  }
}
