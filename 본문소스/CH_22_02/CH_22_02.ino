#include <SoftwareSerial.h>

#define BUFFER_SIZE     5
#define MESSAGE_LENGTH  3 // 정상적인 수신 데이터의 길이
#define NODE_NO   2 // 노드 번호

SoftwareSerial xbee(2, 3);    // (RX, TX)
unsigned long time_previous, time_current;
byte count = 0;         // 카운터
char buffer[5];
int bufferIndex = 0;

void setup() {
  xbee.begin(9600);       // XBee 모듈 연결
  time_previous = millis();
  Serial.begin(9600);
}

void loop() {
  time_current = millis();
  if (time_current - time_previous > 1000) {  // 1초 간격으로 카운터 값 증가
    time_previous = time_current;
    count++;
  }

  if (xbee.available()) {
    char data = xbee.read();
    buffer[bufferIndex] = data;
    bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;

    if (data == '$') {      // 종료 문자 발견
      if (bufferIndex == MESSAGE_LENGTH) {  // 정상적인 메시지 수신
        Serial.print("노드 ");
        Serial.print(int(buffer[0]));
        Serial.print("\t: 카운터 요청");

        if (buffer[0] == NODE_NO) { // 자신에 대한 요청일 때 처리
          Serial.print("\t=> ");
          Serial.println(count);

          // 응답 형식 : ‘송신 노드 번호’ + ‘카운터 값’ + ‘$’
          xbee.write(NODE_NO);    // 노드 번호
          xbee.write(count);
          xbee.write('$');
        }
        else {
          Serial.println();
        }
      }
      else {
        Serial.println("* 잘못된 카운터 요청 수신...");
      }
      bufferIndex = 0;
    }
  }
}
