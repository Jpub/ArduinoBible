#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 4);     // 소프트웨어 시리얼 포트 (RX, TX)
int relay_control = 2;      // 릴레이 제어 핀 연결

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(relay_control, OUTPUT);   // 릴레이 제어 핀을 출력으로 설정
  digitalWrite(relay_control, LOW);   // 열린 상태에서 시작

  Serial.println("* 릴레이는 열린 상태입니다.");
  BTSerial.println("* 릴레이는 열린 상태입니다.");
}

void loop() {
  if (BTSerial.available()) {     // 블루투스로 문자 수신
    char c = BTSerial.read();

    Serial.print(String('\'') + c + "\' : ");
    BTSerial.print(String('\'') + c + "\' : ");
    if (c == 'o' || c == 'O') {     // ‘o‘ 또는 ’O‘ : 릴레이 닫기
      Serial.println("릴레이를 닫습니다.");
      BTSerial.println("릴레이를 닫습니다.");
      digitalWrite(relay_control, HIGH);
    }
    else {          // 이외 모든 문자 : 릴레이 열기
      Serial.println("릴레이를 엽니다.");
      BTSerial.println("릴레이를 엽니다.");
      digitalWrite(relay_control, LOW);
    }
  }
}
