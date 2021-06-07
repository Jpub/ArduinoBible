#include <WiFiEsp.h>
#include <SoftwareSerial.h>

#define QUERY_INTERVAL  5000  // 시간 정보 요청 간격
#define NTP_TIMEOUT     1000  // NTP 서버 응답 대기 시간 1초

#define STATE_IDLE 0      // 시간 정보 요청 대기 상태
#define STATE_RECEIVING_INFO 1  // 시간 정보 요청 후 정보 수신 상태

SoftwareSerial ESPSerial(2, 3);     // ESP-01 모듈 연결 포트

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";

String timeServer = "kr.pool.ntp.org";  // NTP 서버

const int MAX_LINE_LENGTH = 50;
char buffer[MAX_LINE_LENGTH + 1]; // 데이터 수신 버퍼
int index = 0;        // 버퍼 내 데이터 저장 위치
String timeString = "";     // ESP-01 모듈이 반환하는 시간 문자열

int state = STATE_IDLE;       // 시간 정보 요청 대기 상태로 시작

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

  // NTP 설정
  if (!sendATcommand("AT+CIPSNTPCFG=1,9,\"" + timeServer + '\"', "OK", 1)) {
    Serial.println(F("* NTP 초기화 과정에서 오류가 발생했습니다."));
    while (1);
  }
  else {
    Serial.println(F("* NTP를 초기화 했습니다."));
  }
  Serial.println();

  time_previous = millis();
}

// 지정한 시간 내에 지정한 응답 수신 여부로 AT 명령 실행 성공 여부 판단
boolean sendATcommand(String command, char *response, int second) {
  // 최대 대기 시간 설정
  ESPSerial.setTimeout(second * 1000);
  // AT 명령을 ESP-01 모듈로 전달하여 실행
  ESPSerial.println(command);
  // 응답 대기
  boolean responseFound = ESPSerial.find(response);
  // 최대 대기 시간을 디폴트값인 1초로 변경
  ESPSerial.setTimeout(1000);

  return responseFound;     // AT 명령 실행 성공 여부 반환
}

void loop() {
  time_current = millis();

  // 이전 시간 정보 요청 이후 일정 시간이 지났을 때 다시 시간 정보 요청
  if (state == STATE_IDLE) {
    if (time_current - time_previous > QUERY_INTERVAL) {
      Serial.println(F("* NTP 서버에 시간 정보를 요청합니다."));

      // NTP 서버에서 시간 정보를 요청하는 AT 명령 실행
      ESPSerial.println("AT+CIPSNTPTIME?");

      time_previous = millis();
      state = STATE_RECEIVING_INFO;
    }
  }
  else if (state == STATE_RECEIVING_INFO) {
    // 서버로부터 데이터 수신이 지연된 경우
    if (time_current - time_previous > NTP_TIMEOUT) {
      Serial.println(F(" => 시간 정보 수신 과정에서 오류가 발생했습니다."));
      Serial.println();

      time_previous = millis();
      state = STATE_IDLE;
    }
    else {
      processReceivedInformation();   // 데이터 수신 및 처리
    }
  }
  time_current = millis();
}

void processReceivedInformation() {
  if (ESPSerial.available()) {
    char ch = ESPSerial.read();
    buffer[index] = ch;
    index = (index + 1) % MAX_LINE_LENGTH;
    buffer[index] = 0;

    if (ch == '\n') {
      if (strstr(buffer, "OK")) {     // 명령 실행 완료 문장
        Serial.println(" => " + timeString);
        time_previous = millis();
        state = STATE_IDLE;
        timeString = "";
      }
      else if (strstr(buffer, "+CIPSNTPTIME")) {  // 시간 정보 문자열 포함 문장
        int N = strlen(buffer);
        for (int i = 13; i < N; i++) {  // 콜론 이후 개행 문자 전까지
          if (buffer[i] != '\r' && buffer[i] != '\n') {
            timeString += buffer[i];
          }
        }
      }
      index = 0;
    }
  }
}
