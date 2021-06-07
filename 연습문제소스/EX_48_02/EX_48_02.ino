#include <SoftwareSerial.h>

const int MIN_INTERVAL = 500, MAX_INTERVAL = 2000;
int current_interval = 1000;

SoftwareSerial BTSerial(3, 4);     // 소프트웨어 시리얼 포트 (RX, TX)
int relay_control = 2;      // 릴레이 제어 핀 연결

boolean led_state = false;
unsigned long time_previous = 0;
String buffer = "";
boolean process_it = false;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(relay_control, OUTPUT);   // 릴레이 제어 핀을 출력으로 설정
  digitalWrite(relay_control, LOW);   // 열린 상태에서 시작

  Serial.println("* 현재 점멸 간격은 " + String(current_interval) + "밀리초입니다.");
}

void loop() {
  unsigned long time_current = millis();

  if (BTSerial.available()) {     // 블루투스로 문자 수신
    char c = BTSerial.read();

    if (c == '\n') {
      process_it = true;
    }
    else {
      buffer += c;
    }
  }

  if (process_it) {
    int new_interval = buffer.toInt();
    Serial.print(" => " + buffer + " : ");

    if (new_interval >= MIN_INTERVAL && new_interval <= MAX_INTERVAL && new_interval != current_interval) {
      current_interval = new_interval;
      Serial.println(new_interval + String("밀리초로 점멸 간격을 변경합니다."));
    }
    else {
      Serial.println("현재 점멸 간격을 유지합니다.");
    }

    process_it = false;
    buffer = "";
  }

  if (time_current - time_previous >= current_interval) {
    led_state = !led_state;
    digitalWrite(relay_control, led_state);
    time_previous = time_current;
  }
}
