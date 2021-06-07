#include <openGLCD.h>

void setup() {
  GLCD.Init();        // 그래픽 LCD 초기화
  GLCD.SelectFont(System5x7);     // 출력 폰트 선택

  Serial.begin(9600);     // 시리얼 통신 초기화
}

void loop() {
  int reading = analogRead(A5);     // 온도 센서 읽기
  // 전압에 100을 곱하면 섭씨 온도를 얻을 수 있다.
  float temperature = reading / 1024.0 * 500;

  Serial.print("Temperature : ");   // 시리얼 모니터로 출력
  Serial.print(temperature, 2);
  Serial.println(" C");

  GLCD.print("Temperature : ");   // 시리얼 모니터와 같은 방법으로
  GLCD.print(temperature, 2);   // 그래픽 LCD로 출력
  GLCD.println(" C");

  delay(1000);
}
