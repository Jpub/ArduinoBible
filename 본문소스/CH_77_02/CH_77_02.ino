#include <ATtinySerialOut.h>

void setup() {
  Serial.begin(115200);     // 속도 설정 주의
}

void loop() {
  Serial.println();
  Serial.println("* ASCII Table ~ Character Map");

  for (byte thisByte = 33; thisByte < 127; thisByte++) {
    Serial.write(thisByte);

    Serial.print(", dec: ");
    Serial.print(thisByte);
    Serial.print(", hex: ");
    Serial.print(thisByte, HEX);
    Serial.print(", oct: ");
    Serial.print(thisByte, OCT);
    Serial.print(", bin: ");
    Serial.println(thisByte, BIN);
  }

  delay(5000);
}
