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
      int N = buffer.length();    // 수신 데이터 길이
      int no = buffer.substring(0, N - 1).toInt();  // 수신 문자열을 변환
      Serial.print(String("슬레이브로부터 수신한 값 : ") + no);

      byte checksum = 0;    // 체크섬 계산
      for (int i = 0; i < N - 1; i++) {
        checksum = checksum ^ buffer[i];
      }

      if (checksum == buffer[N - 1]) {  // 수신한 체크섬과 계산한 체크섬 비교
        Serial.println(" (체크섬 정상)");
      }
      else {
        Serial.println(" (체크섬 에러)");
      }

      buffer = "";      // 버퍼 비우기
    }
    else {
      buffer += (char)data;     // 버퍼에 저장
    }
  }
}
