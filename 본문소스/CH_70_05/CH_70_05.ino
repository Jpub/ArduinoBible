#include <Time.h>
#include <TimeLib.h>

#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>
#include <NTPClient.h>

#define QUERY_INTERVAL 5000     // 시간 정보 요청 간격

SoftwareSerial ESPSerial(2, 3);     // ESP-01 모듈 연결 포트

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";

char timeServer[] = "kr.pool.ntp.org";  // NTP 서버
unsigned int localPort = 123;     // 클라이언트에서 사용하는 포트

WiFiEspUDP Udp;       // UDP 객체
NTPClient timeClient(Udp, timeServer);  // NTPClient 객체

unsigned long time_previous, time_current;

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 UART 시리얼 연결
  ESPSerial.begin(9600);      // ESP-01 모듈과의 UART 시리얼 연결

  // 'AT'에 대한 응답 확인, 리셋, 스테이션 모드 설정, SDK 버전 호환 확인
  WiFi.init(&ESPSerial);      // ESP-01 모듈 초기화

  // AP 접속
  Serial.println(String("* \'") + AP + F("\'에 연결을 시도합니다."));
  if (WiFi.begin(AP, PW) != WL_CONNECTED) {
    Serial.println(F("* AP에 연결할 수 없습니다."));
    while (1);
  }
  else {
    Serial.println(F("* AP에 연결되었습니다."));
  }
  Serial.println();

  time_previous = millis();
  timeClient.begin(localPort);    // NTPClient 객체 시작
}

void loop() {
  time_current = millis();

  // 이전 시간 정보 요청 이후 일정 시간이 지났을 때 다시 시간 정보 요청
  if (time_current - time_previous > QUERY_INTERVAL) {
    Serial.println(F("* NTP 서버에 시간 정보를 요청합니다."));
    if (timeClient.update()) {
      unsigned long ntpTime = timeClient.getEpochTime();
      printServerTime(ntpTime);
    }
    else {
      Serial.println(" => 시간 업데이트에 오류가 발생했습니다.");
    }

    time_previous = millis();
  }
}

void printServerTime(unsigned long timestamp) {
  char timeString[] = "YYYY:MM:DD, HH:MM:SS";
  sprintf(timeString, "%04d:%02d:%02d, %02d:%02d:%02d",
          year(timestamp), month(timestamp), day(timestamp),
          hour(timestamp), minute(timestamp), second(timestamp));

  Serial.println(String(" => ") + timeString);
}
