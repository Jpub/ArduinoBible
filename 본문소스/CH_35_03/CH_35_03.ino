#include <SoftwareSerial.h>

SoftwareSerial gps(2, 3);       // GPS 리시버 연결 포트 (RX, TX)
String sentence = "";       // NMEA 문장 버퍼
boolean process_sentence = false;   // 문장이 끝난 경우

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 연결
  gps.begin(9600);      // GPS 리시버와의 시리얼 연결
}

void loop() {
  if (gps.available()) {      // GPS 리시버에서 데이터 수신
    char data = gps.read();
    switch (data) {
      case '\r':        // '\r'은 무시
        break;
      case '\n':        // 문장의 끝
        process_sentence = true;
        break;
      default:          // 나머지는 버퍼에 저장
        sentence = sentence + data;
        break;
    }
  }

  if (process_sentence) {     // 문장이 끝난 경우
    process_sentence = false;
    if (sentence.startsWith("$GPGGA")) {  // GGA 문장 여부 판단
      Serial.println(sentence);   // GGA 문장 출력
    }
    sentence = "";      // 문장 버퍼 비움
  }
}
