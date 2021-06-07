#include <SoftwareSerial.h>

char TERMINATOR = '\n';
int LEDs[] = { 6, 7, 8, 9, 10, 11, 12, 13 };  // LED 연결 핀
String buffer = "";
boolean process_it = false;

SoftwareSerial BTSerial(2, 3);    // 소프트웨어 시리얼 포트 (RX, TX)

void setup() {
  BTSerial.begin(9600);       // 블루투스 모듈과의 시리얼 통신 초기화

  for (int i = 0; i < 8; i++) {     // LED 연결 핀을 출력으로 설정
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LOW);   // 디폴트 상태는 꺼진 상태
  }
}

void loop() {
  if (BTSerial.available()) {     // 블루투스를 통한 데이터 수신 확인
    char ch = BTSerial.read();    // 한 문자 읽기

    if (ch == TERMINATOR) {
      process_it = true;
    }
    else {
      buffer = buffer + ch;
    }
  }

  if (process_it) {
    int no = buffer.toInt();
    BTSerial.print(buffer + " : ");
    if (no >= 0 && no <= 255) {
      BTSerial.println(no, BIN);

      for (int i = 0; i < 8; i++) {
        boolean b = (no >> i) & 0x01;
        digitalWrite(LEDs[i], b);
      }
    }
    else {
      BTSerial.println("잘못된 값이 입력되었습니다.");
    }

    process_it = false;
    buffer = "";
  }
}
