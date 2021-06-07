#include <IRremote.h>

int RECV_PIN = 2;       // 적외선 수신기의 DATA 핀 연결
IRrecv irrecv(RECV_PIN);    // 적외선 수신기 객체 생성
decode_results results;       // 수신 데이터

unsigned int button_data[] = {    // 0~9 리모컨 버튼 데이터
  0x6897, 0x30CF, 0x18E7, 0x7A85, 0x10EF,
  0x38C7, 0x5AA5, 0x42BD, 0x4AB5, 0x52AD
};

int pinsLED[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11 };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 9; i++) {
    pinMode(pinsLED[i], OUTPUT);  // LED 연결 핀을 출력으로 설정
    digitalWrite(pinsLED[i], LOW);    // LED는 꺼진 상태에서 시작
  }

  irrecv.enableIRIn();      // 적외선 수신기 시작
}

void loop() {
  if (irrecv.decode(&results)) {    // 수신 성공
    char buffer[9];
    Serial.print("수신 데이터 : 0x");
    sprintf(buffer, "%08lX", results.value);  // 8자의 16진수로 변환
    Serial.print(String(buffer) + " => ");

    // 데이터 코드 2바이트만 사용
    unsigned int remote_data = results.value & 0xFFFF;
    int key = -1;
    for (int i = 0; i <= 9; i++) {
      if (remote_data == button_data[i]) {
        key = i;        // 리모컨의 숫자 버튼 확인
      }
    }
    if (key == -1) {      // 숫자 버튼이 아닌 경우나 계속 누른 경우
      Serial.println("알 수 없는 버튼");
    }
    else {
      Serial.println(String(key) + "개의 LED를 켭니다.");
      for (int i = 0; i < 9; i++) {   // 숫자 버튼에 따라 LED 개수 조절
        digitalWrite(pinsLED[i], i < key);
      }
    }

    irrecv.resume();      // 다음 데이터 수신
  }

  delay(100);
}
