#include <Time.h>
#include <TimeLib.h>

#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>

#define QUERY_INTERVAL 5000    // 시간 정보 요청 간격
#define UDP_TIMEOUT 2000    // 서버 응답 대기 시간 2초

#define STATE_IDLE    0   // 시간 정보 요청 대기 상태
#define STATE_RECEIVING_INFO  1 // 시간 정보 요청 후 정보 수신 상태

SoftwareSerial ESPSerial(2, 3);   // ESP-01 모듈 연결 포트

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";

char timeServer[] = "kr.pool.ntp.org";  // NTP 서버
unsigned int localPort = 123;   // 클라이언트에서 사용하는 포트

const int NTP_PACKET_SIZE = 48; // NTP 패킷 크기
byte buffer[NTP_PACKET_SIZE];     // 데이터 수신 버퍼

int state = STATE_IDLE;     // 시간 정보 요청 대기 상태로 시작

WiFiEspUDP Udp;       // UDP 객체

unsigned long time_previous, time_current;

void setup() {
  Serial.begin(9600);     // 컴퓨터와의 UART 시리얼 연결
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
  Udp.begin(localPort);     // UDP 시작
}

void loop() {
  time_current = millis();

  // 이전 시간 정보 요청 이후 일정 시간이 지났을 때 다시 시간 정보 요청
  if (state == STATE_IDLE) {
    if (time_current - time_previous > QUERY_INTERVAL) {
      Serial.println(F("* NTP 서버에 시간 정보를 요청합니다."));
      sendNTPpacket(timeServer);  // 시간 정보 요청을 위한 NTP 패킷 전송

      time_previous = millis();
      state = STATE_RECEIVING_INFO;
    }
  }
  else if (state == STATE_RECEIVING_INFO) {
    // 서버로부터 데이터 수신이 지연된 경우
    if (time_current - time_previous > UDP_TIMEOUT) {
      Serial.println(F(" => 시간 정보 수신 과정에서 오류가 발생했습니다."));
      Serial.println();

      time_previous = millis();
      state = STATE_IDLE;
    }
    else {
      processReceivedInformation();   // 데이터 수신 및 처리
    }
  }
}

void sendNTPpacket(char *ntpSrv) {
  memset(buffer, 0, NTP_PACKET_SIZE);   // 모든 데이터를 0으로 설정
  buffer[0] = 0x1B;       // 버전 3, 클라이언트 모드

  Udp.beginPacket(ntpSrv, 123);     // NTP 서버 123번 포트로 요청 시작
  Udp.write(buffer, NTP_PACKET_SIZE); // 데이터 전송
  Udp.endPacket();      // 요청 끝
}

void processReceivedInformation() {
  if (Udp.available()) {
    // 1초 이내로 48바이트 데이터 읽기
    int readNo = Udp.read(buffer, NTP_PACKET_SIZE);

    if (readNo != NTP_PACKET_SIZE) {  // 데이터 수신 지연
      Serial.println(F(" => 시간 정보 데이터에 오류가 발생했습니다."));
    }
    else {
      processTimeInfo();      // 수신한 정보 처리
    }
    Serial.println();

    time_previous = millis();
    state = STATE_IDLE;
  }
}

void processTimeInfo() {
  // 41번째 바이트부터 4바이트에 서버에서 보낸 서버 시간이 포함되어 있다.
  unsigned long highWord = word(buffer[40], buffer[41]);
  unsigned long lowWord = word(buffer[42], buffer[43]);
  // 1900년 1월 1일 이후 경과한 초 수
  unsigned long after19000101 = highWord << 16 | lowWord;

  Serial.print(" => 1900년 1월 1일 이후 경과한 초 : ");
  Serial.println(after19000101);

  // 유닉스 시간은 1970년 1월 1일 이후 경과한 초 수로 나타낸다.
  const unsigned long seventyYears = 2208988800UL;
  time_t timestamp = after19000101 - seventyYears;

  char timeString[] = "YYYY:MM:DD, HH:MM:SS";
  // Time 라이브러리를 사용하여 연월일시분초로 변환
  sprintf(timeString, "%04d:%02d:%02d, %02d:%02d:%02d",
          year(timestamp), month(timestamp), day(timestamp),
          hour(timestamp), minute(timestamp), second(timestamp));

  Serial.println(String(" => ") + timeString);
}
