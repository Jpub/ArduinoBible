#include <SoftwareSerial.h>

SoftwareSerial USB_UART(2, 3);     // (RX, TX)

void setup() {
  Serial.begin(9600);     // 하드웨어 시리얼 포트 초기화
  USB_UART.begin(9600);     // 소프트웨어 시리얼 포트 초기화
}

void loop() {
  if (Serial.available()) {     // 하드웨어 시리얼 포트 입력을
    USB_UART.write(Serial.read());  // 소프트웨어 시리얼 포트로 출력
  }

  if (USB_UART.available()) {   // 소프트웨어 시리얼 포트 입력을
    Serial.write(USB_UART.read());  // 하드웨어 시리얼 포트로 출력
  }
}
