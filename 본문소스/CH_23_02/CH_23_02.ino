#include <IRremote.h>

IRsend irsend;        // 적외선 데이터 송신 객체

unsigned long button_data[] = {   // 0~9 리모컨 버튼 데이터
  0xFF6897, 0xFF30CF, 0xFF18E7, 0xFF7A85, 0xFF10EF,
  0xFF38C7, 0xFF5AA5, 0xFF42BD, 0xFF4AB5, 0xFF52AD
};
int index = 0;        // 전송할 데이터 인덱스

void setup() {
  Serial.begin(9600);
}

void loop() {
  char buffer[9];
  Serial.print("데이터 전송 : 0x");
  sprintf(buffer, "%08lX", button_data[index]); // 8자리 16진수로 변환
  Serial.println(buffer);

  irsend.sendNEC(button_data[index], 32); // NEC 방식의 4바이트 데이터 전송

  index = (index + 1) % 10;   // 다음 전송할 데이터 인덱스

  delay(1000);
}
