#include <SoftwareSerial.h>

#define BUFFER_SIZE     5
#define MESSAGE_LENGTH  3 // 정상적인 수신 데이터의 길이

SoftwareSerial xbee(2, 3);    // (RX, TX)
unsigned long time_previous, time_current;
char buffer[BUFFER_SIZE];
int bufferIndex = 0;
byte nodeNo;        // 카운터를 요청할 노드 번호

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);       // XBee 모듈 연결
  time_previous = millis();
  nodeNo = 0;
}

void loop() {
  time_current = millis();
  // 1초 간격으로 노드 2와 3에 번갈아 현재 카운터 값 요청
  if (time_current - time_previous > 1000) {
    time_previous = time_current;

    // 요청 형식 : ‘수신 노드 번호’ + ‘C’ + ‘$’
    xbee.write(nodeNo + 2);   // 2번과 3번 노드에 번갈아 요청
    nodeNo = (nodeNo + 1) % 2;
    xbee.write('C');      // 카운터 값 요청 문자 ‘C’
    xbee.write('$');
  }

  if (xbee.available()) {
    byte data = xbee.read();
    buffer[bufferIndex] = data;
    bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;

    if (data == '$') {      // 종료 문자 발견
      if (bufferIndex == MESSAGE_LENGTH) {  // 정상적인 메시지 수신
        Serial.print("노드 ");
        Serial.print(int(buffer[0]));
        Serial.print(" \t: 카운터 수신\t=> ");
        Serial.println(int(buffer[1]));
        bufferIndex = 0;
      }
      else {
        Serial.println("* 잘못된 카운터 데이터 수신...");
      }
    }
  }
}
