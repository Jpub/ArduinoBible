#include <openGLCD.h>

void setup() {
  GLCD.Init();        // 그래픽 LCD 초기화

  GLCD.SelectFont(System5x7);   // 출력 폰트 선택

  GLCD.println("Hello World!");   // 문자열 출력
  GLCD.println(78, BIN);      // 정수를 이진수로 출력
  GLCD.println(78, DEC);      // 정수를 십진수로 출력
  GLCD.println(78, HEX);      // 정수를 십육진수로 출력
  GLCD.println(1.23456, 2);   // 실수를 소수점 이하 두 자리로 출력
}

void loop() {
}
