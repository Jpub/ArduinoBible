#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(2, 3);       // GPS 리시버 연결 포트 (RX, TX)
boolean new_data = false;   // 새로운 문장 수신 플래그

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 연결
  ss.begin(9600);       // GPS 리시버와의 시리얼 연결
}

void loop() {
  while (ss.available()) {
    char c = ss.read();
    if (gps.encode(c)) {      // 새로운 문장 처리 성공
      new_data = true;
    }
  }

  if (new_data) {
    new_data = false;

    float latitude, longitude;
    int year;
    byte month, day, hour, min, sec;

    gps.f_get_position(&latitude, &longitude);
    gps.crack_datetime(&year, &month, &day, &hour, &min, &sec);

    Serial.print(fixedWidthStr(year, 4) + "년 ");
    Serial.print(fixedWidthStr(month, 2) + "월 ");
    Serial.print(fixedWidthStr(day, 2) + "일, ");

    Serial.print(fixedWidthStr(hour, 2) + "시 ");
    Serial.print(fixedWidthStr(min, 2) + "분 ");
    Serial.print(fixedWidthStr(sec, 2) + "초, (");

    Serial.print(latitude, 3);    // 위도
    Serial.print(", ");
    Serial.print(longitude, 3);   // 경도
    Serial.println(")");
  }
}

String fixedWidthStr(int n, int width) {  // 정수를 지정한 길이 문자열로 변환
  String str = "";

  for (int i = 0; i < width; i++) {
    int remain = n % 10;
    n = n / 10;
    str = char(remain + '0') + str;
  }

  return str;
}
