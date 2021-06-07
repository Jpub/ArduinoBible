#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mcp;      // MCP23017 객체
uint16_t value_previous = 0xFF, value_current = 0;

void setup() {
  Serial.begin(9600);
  mcp.begin();        // 기본 0x20 주소를 사용한 초기화

  for (int i = 0; i < 8; i++) {
    mcp.pinMode(i, OUTPUT);     // 뱅크 A는 출력
    mcp.digitalWrite(i, LOW);   // LED는 꺼진 상태
    mcp.pinMode(i + 8, INPUT);    // 뱅크 B는 입력
    mcp.pullUp(i + 8, true);    // 버튼 연결 핀의 풀업 저항 사용
  }
}

void loop() {
  // 뱅크 B에 연결된 8개 버튼의 상태, 풀업 저항 사용으로 반전시킴
  value_current = ~(mcp.readGPIOAB() >> 8);

  if (value_current != value_previous) {  // 버튼 상태가 바뀐 경우
    value_previous = value_current;
    mcp.writeGPIOAB(value_current); // 뱅크 A에 연결된 LED로 출력
    displayButtonState(value_current);  // 시리얼 모니터로 버튼 상태 출력
    delay(10);
  }
}

void displayButtonState(uint8_t state) {
  Serial.print("현재 버튼 상태 : ");
  for (int i = 0; i < 8; i++) {
    boolean onoff = (state >> (7 - i)) & 0x01;
    Serial.print(onoff ? "O " : ". ");
  }
  Serial.println();
}
