#include <IRremote.h>

int RECV_PIN = 11;       // 적외선 수신기의 DATA 핀 연결
IRrecv irrecv(RECV_PIN);    // 적외선 수신기 객체 생성
decode_results results;       // 수신 데이터

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn();      // 적외선 수신기 시작
}

void loop() {
  if (irrecv.decode(&results)) {    // 수신 성공
    char buffer[9];
    Serial.print("수신 데이터 : 0x");
    sprintf(buffer, "%08lX", results.value);  // 8자의 16진수로 변환
    Serial.println(buffer);

    irrecv.resume();      // 다음 데이터 수신
  }

  delay(100);
}
