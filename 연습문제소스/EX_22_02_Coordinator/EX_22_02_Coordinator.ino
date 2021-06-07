#include <SoftwareSerial.h>

#define BUFFER_SIZE     10
#define MESSAGE_LENGTH  6 // 정상적인 수신 데이터의 길이

SoftwareSerial xbee(2, 3);    // (RX, TX)

char buffer[BUFFER_SIZE];
int bufferIndex = 0;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);       // Xbee 모듈 연결
}

void loop() {
  if (xbee.available()) {
    byte data = xbee.read();
    buffer[bufferIndex] = data;
    bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;

    if (data == '$') {      // 종료 문자 발견
      if (bufferIndex == MESSAGE_LENGTH) {  // 정상적인 메시지 수신
        Serial.print("노드 ");
        Serial.print(int(buffer[0]));
        Serial.print(" \t: 아날로그 입력 값\t=> ");

        buffer[bufferIndex] = 0;
        int vr = String(buffer).substring(1, 5).toInt();
        Serial.println(vr);
        bufferIndex = 0;
      }
      else {
        Serial.println("* 잘못된 데이터 수신...");
      }
    }
  }
}
