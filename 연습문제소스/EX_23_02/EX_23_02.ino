#include <IRremote.h>

int RECV_PIN = 2;       // 적외선 수신기의 DATA 핀 연결
IRrecv irrecv(RECV_PIN);    // 적외선 수신기 객체 생성
decode_results results;       // 수신 데이터

int pinLED = 10;
int intensity = 100; // 초기 LED 밝기
int STEP = 10;

// '+', '-' 버튼 데이터
unsigned long btn_plus = 0xFF02FD, btn_minus = 0xFF9867;
unsigned long last_receive_time = 0, last_receive_value;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();      // 적외선 수신기 시작
  analogWrite(pinLED, intensity);
}

void loop() {
  if (irrecv.decode(&results)) {    // 수신 성공
    char buffer[9];

    unsigned long value = results.value;
    Serial.print("수신 데이터 : 0x");
    sprintf(buffer, "%08lX", value);  // 8자의 선행 영을 포함한 16진수로 변환
    Serial.print(buffer + String(" : "));

    unsigned long current_time = millis();
    if (value == 0xFFFFFFFF && current_time - last_receive_time < 115) {
      value = last_receive_value;
      last_receive_time = current_time;
    }
    else {
      last_receive_time = current_time;
      last_receive_value = value;
    }

    if (value == btn_plus) {
      intensity += STEP;
      if (intensity >= 255) {
        intensity = 255;
      }
      Serial.println(intensity + String("까지 증가"));

      analogWrite(pinLED, intensity);
    }
    else if (value == btn_minus) {
      intensity -= STEP;
      if (intensity < 0) {
        intensity = 0;
      }
      Serial.println(intensity + String("까지 감소"));

      analogWrite(pinLED, intensity);
    }
    else {
      Serial.println(intensity + String(" 유지"));
    }

    irrecv.resume();      // 다음 데이터 수신
  }

  //delay(100);
}
