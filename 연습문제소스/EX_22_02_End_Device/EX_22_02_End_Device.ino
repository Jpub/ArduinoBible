#include <SoftwareSerial.h>

#define NODE_NO   2 // 노드 번호

SoftwareSerial xbee(2, 3);    // (RX, TX)
unsigned long time_previous, time_current;

void setup() {
  xbee.begin(9600);       // Xbee 모듈 연결
  time_previous = millis();
}

void loop() {
  time_current = millis();
  if (time_current - time_previous > 1000) {
    time_previous = time_current;

    int vr = analogRead(A0);
    char buffer[5];
    sprintf(buffer, "%04d", vr);

    xbee.write(NODE_NO);
    xbee.print(buffer);
    xbee.write('$');
  }
}
