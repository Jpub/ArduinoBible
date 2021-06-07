#include <NewPing.h>

NewPing ultrasonic(3, 2);     // (트리거 핀, 에코 핀)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int pulseWidth = ultrasonic.ping_median();
  int distanceCM = ultrasonic.convert_cm(pulseWidth);
  int distanceIN = ultrasonic.convert_in(pulseWidth);

  Serial.print("전방 장애물까지 거리 = ");
  Serial.print(String(distanceCM) + " cm,\t");
  Serial.println(String(distanceIN) + " inch");

  delay(1000);
}
