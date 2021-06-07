#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mcp;      // MCP23017 객체

void setup() {
  mcp.begin();        // 기본 0x20 주소를 사용한 초기화

  for (int i = 0; i < 8; i++) {
    mcp.pinMode(i, OUTPUT);     // 뱅크 A는 출력
    mcp.digitalWrite(i, LOW);   // LED는 꺼진 상태
    mcp.pinMode(i + 8, INPUT);    // 뱅크 B는 입력
    mcp.pullUp(i + 8, true);    // 버튼 연결 핀의 풀업 저항 사용
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {
    boolean b = mcp.digitalRead(i + 8); // 버튼 상태 읽기
    mcp.digitalWrite(i, !b);    // 풀업 저항 사용으로 반전 출력
  }

  delay(10);
}
