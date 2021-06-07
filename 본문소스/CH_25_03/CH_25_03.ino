#include <SoftwareSerial.h>
#include <stdlib.h>

SoftwareSerial BLE(3, 2);      // (RX, TX) -> (HM-10 TX, HM-10 RX)
boolean process_it = false;   // 수신 문장 처리 여부
boolean scan_start = false;   // 스캔 명령 실행 여부

String buffer = "";     // HM-10 모듈의 출력 저장 버퍼
String MY_BEACON_MAJOR = "1234";  // 비콘의 메이저 번호

int INTERVAL = 2000;      // 스캔 간격, 밀리초 단위
unsigned long t_previous, t_current;

void setup() {
  BLE.begin(115200);      // HM-10 모듈과의 통신 속도
  Serial.begin(115200);       // 시리얼 모니터와의 통신 속도

  t_previous = millis();
}

void loop() {
  t_current = millis();

  // 이전 스캔이 끝나고 최소 INTERVAL 시간이 지났을 때 다시 스캔
  if (!scan_start && (t_current - t_previous) >= INTERVAL) {
    t_previous = t_current;

    BLE.println("AT+DISI?");    // 스캔 시작 명령
    Serial.println("** 비콘 스캔을 시작합니다.");
    scan_start = true;
  }

  if (BLE.available() > 0) {    // HM-10 모듈의 출력 저장
    char ch = BLE.read();
    if (ch == '\n') {     // 문장의 끝
      process_it = true;      // 문장 단위의 처리
    }
    else {
      buffer += ch;
    }
  }

  if (process_it) {
    process_it = false;
    buffer.trim();        // 수신 문장에서 화이트 스페이스 제거

    if (buffer.equals("OK+DISCE")) {  // 스캔 데이터 수신 종료
      scan_start = false;
      Serial.println("** 비콘 스캔이 끝났습니다.\n");
      t_previous = millis();
    }
    else if (buffer.equals("OK+DISIS")) {   // 스캔 데이터 수신 시작
      Serial.println("** 비콘 데이터를 받기 시작합니다.");
    }
    else {
      if (buffer.startsWith("OK+DISC")) { // 비콘 데이터 문장인 경우
        int pos[5] = {0, };
        int start = 0;

        for (int i = 0; i < 5; i++) { // 세미콜론으로 분리되는 필드 구분
          pos[i] = buffer.indexOf(':', start + 1);
          start = pos[i];
        }
        // (메이저, 마이너, 전송 전력)을 포함하는 필드
        String info_string = buffer.substring(pos[2] + 1, pos[3]);
        // 메이저 번호, 상위 2바이트
        String major = info_string.substring(0, 4);

        // 가변저항 값을 게시하는 비콘의 메이저 번호와 일치하는 경우
        if (major.equals(MY_BEACON_MAJOR)) {
          String minor = info_string.substring(4, 8); // 마이너 값
          // 16진수 문자열을 정수값으로 변환
          unsigned int minor_no = strtol(minor.c_str(), NULL, 16);
          // 상위 6비트 노드 ID
          unsigned int node_id = minor_no >> 10;
          // 하위 10비트 가변저항 값
          unsigned int value = minor_no & 0x03FF;

          Serial.println(buffer);
          Serial.println(String(" : 메이저 \t=> ") + major);
          Serial.println(String(" : 마이너 \t=> ") + minor);
          Serial.println(String(" : 노드 ID\t=> ") + node_id);
          Serial.println(String(" : 가변저항 값\t=> ") + value);
        }
      }
    }

    buffer = "";
  }
}
