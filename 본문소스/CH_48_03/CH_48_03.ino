#include <SoftwareSerial.h>

const unsigned long BLINKING_INTERVAL = 500;     // LED 점멸 간격
const unsigned long TOTAL_BLINKING_TIME = 5000;   // 5초 동안 LED 점멸

SoftwareSerial BTSerial(3, 4);    // 소프트웨어 시리얼 포트 (RX, TX)
int relay_control = 2;      // 릴레이 제어 핀 연결

boolean blinking_state = false, led_state = false;
unsigned long time_blinking_start;  // LED 점멸을 시작한 시간
unsigned long time_last_led_invert;   // 마지막으로 LED 상태를 바꾼 시간

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(relay_control, OUTPUT);   // 릴레이 제어 핀을 출력으로 설정
  digitalWrite(relay_control, LOW);   // 꺼진 상태에서 시작

  Serial.println("* LED는 꺼진 상태입니다.");
  BTSerial.println("* LED는 꺼진 상태입니다.");
}

void loop() {
  unsigned long time_current = millis();

  if (BTSerial.available()) {     // 블루투스로 문자 수신
    char c = BTSerial.read();

    if (c == 'o' || c == 'O') {   // 점멸 시작 명령
      if (blinking_state == false) {    // 꺼진 상태인 경우
        blinking_state = true;    // 점멸 상태로 설정

        time_blinking_start = time_current; // 점멸 시작 시각
        time_last_led_invert = time_current;  // LED 상태 변경 시각

        led_state = true;       // LED를 켜서 점멸 시작
        digitalWrite(relay_control, led_state);

        Serial.println("* LED 점멸을 시작합니다.");
        BTSerial.println("* LED 점멸을 시작합니다.");
      }
      else {        // 이미 점멸 상태인 경우
        time_blinking_start = millis();   // 5초 다시 시작

        Serial.println("* 5초를 다시 시작합니다.");
        BTSerial.println("* 5초를 다시 시작합니다.");
      }
    }
    else if (c == 'x' || c == 'X') {    // 점멸 종료 명령
      if (blinking_state == true) {   // 점멸 상태인 경우
        blinking_state = false;   // 꺼진 상태로 설정
        led_state = false;      // LED 끄기
        digitalWrite(relay_control, led_state);

        Serial.println("* 종료 명령으로 LED 점멸을 종료합니다.");
        BTSerial.println("* 종료 명령으로 LED 점멸을 종료합니다.");
      }
    }
  }

  if (blinking_state) {     // 점멸 상태인 경우
    // 5초가 지나면 꺼진 상태로 설정
    if (time_current - time_blinking_start >= TOTAL_BLINKING_TIME) {
      blinking_state = false;   // 꺼진 상태로 설정
      led_state = false;      // LED는 꺼진 상태로 설정
      digitalWrite(relay_control, led_state);

      Serial.println("* 시간 만료로 LED 점멸을 종료합니다.");
      BTSerial.println("* 시간 만료로 LED 점멸을 종료합니다.");
    }
    // 점멸 상태일 때 0.5초 간격으로 LED 상태를 반전
    else if (time_current - time_last_led_invert >= BLINKING_INTERVAL) {
      time_last_led_invert = time_current;
      led_state = !led_state;   // LED 상태 반전
      digitalWrite(relay_control, led_state);

      Serial.print("* LED 상태를 ");
      Serial.print(led_state ? "ON으로 " : "OFF로 ");
      Serial.println("설정합니다.");
      BTSerial.print("* LED 상태를 ");
      BTSerial.print(led_state ? "ON으로 " : "OFF로 ");
      BTSerial.println("설정합니다.");
    }
  }
}
