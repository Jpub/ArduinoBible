#include <IRremote.h>

int RECV_PIN = 2;       // 적외선 수신기의 DATA 핀 연결
IRrecv irrecv(RECV_PIN);    // 적외선 수신기 객체 생성
decode_results results;       // 수신 데이터

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();      // 적외선 수신기 시작
}

void loop() {
  if (irrecv.decode(&results)) {    // 수신 성공
    char buffer[9];

    unsigned long value = results.value;
    Serial.print("수신 데이터 : 0x");
    sprintf(buffer, "%08lX", value);  // 8자의 선행 영을 포함한 16진수로 변환
    Serial.println(buffer);

    Serial.print("   데이터 검사 : 0x");
    uint8_t check1 = (value >> 24) | (value >> 16);
    uint8_t check2 = (value >> 8) | value;
    Serial.print(check1, HEX);
    Serial.print(", 0x");
    Serial.print(check2, HEX);
    Serial.print(" => ");
    Serial.println( ((check1 == 0xFF) & (check2 == 0xFF)) ? "Okay" : "Error");

    irrecv.resume();      // 다음 데이터 수신
  }

  delay(100);
}
