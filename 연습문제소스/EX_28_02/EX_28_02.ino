#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mcp;      // MCP23017 객체
int high_button_previous = -1, high_button_current;

void setup() {
  Serial.begin(9600);
  mcp.begin();        // 기본 0x20 주소를 사용한 초기화

  for (int i = 0; i < 8; i++) {
    mcp.pinMode(i, OUTPUT);     // 뱅크 A는 출력
    mcp.digitalWrite(i, LOW);     // LED는 꺼진 상태
    mcp.pinMode(i + 8, INPUT);    // 뱅크 B는 입력
  }
}

void loop() {
  uint8_t buttons = (mcp.readGPIOAB() >> 8);
  high_button_current = -1;
  for (int i = 7; i >= 0; i--) {
    if ( (buttons >> i) & 0x01 ) {
      high_button_current = i;
      break;
    }
  }

  if (high_button_current != high_button_previous) {
    high_button_previous = high_button_current;
    uint16_t LEDs = 0xFF >> (7 - high_button_current);
    mcp.writeGPIOAB(LEDs);

    Serial.println(String("눌러진 가장 상위 버튼 번호 : ") + high_button_current);
    delay(10);
  }
}
