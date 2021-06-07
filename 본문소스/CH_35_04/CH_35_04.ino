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
      processSentence();      // GGA 문장 내 정보 추출
    }
    sentence = "";      // 문장 버퍼 비움
  }
}

void processSentence() {
  int pos[6] = {0, };       // 콤마의 위치
  int start = 0;        // 검색 시작 위치

  Serial.println(sentence);   // 전체 문장 출력

  for (int i = 0; i < 6; i++) {     // 6개 콤마 위치 검색
    pos[i] = sentence.indexOf(',', start + 1);
    start = pos[i];
  }

  // 콤마 사이의 부분 문자열 추출 및 출력
  Serial.print("현재 시각\t: ");
  Serial.println(sentence.substring(pos[0] + 1, pos[1]));
  Serial.print("위도\t: ");
  Serial.print(sentence.substring(pos[1] + 1, pos[2]));
  Serial.println(sentence.substring(pos[2] + 1, pos[3]));
  Serial.print("경도\t: ");
  Serial.print(sentence.substring(pos[3] + 1, pos[4]));
  Serial.println(sentence.substring(pos[4] + 1, pos[5]));
  Serial.println();
}
