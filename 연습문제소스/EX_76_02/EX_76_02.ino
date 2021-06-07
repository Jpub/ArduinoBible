#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX
int count = 0;

void setup() {
  mySerial.begin(9600);
}

void loop() {
  mySerial.printf("* 현재 카운터 값 : %d\n", count++);

  delay(1000);
}
