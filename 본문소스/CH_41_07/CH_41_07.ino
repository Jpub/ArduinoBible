#include <openGLCD.h>

gText upperArea;      // 위쪽 절반
gText lowerArea;        // 아래쪽 절반

int count = 0;        // 위쪽에 표시할 카운터

void setup() {
  GLCD.Init();        // 그래픽 LCD 초기화

  upperArea.DefineArea(textAreaTOP);  // 위쪽 영역 정의
  upperArea.SelectFont(lcdnums12x16); // 위쪽 영역 폰트 선택

  lowerArea.DefineArea(textAreaBOTTOM); // 아래쪽 영역 정의
  lowerArea.SelectFont(System5x7);  // 아래쪽 영역 폰트 선택
}

void loop() {
  count = (count + 1) % 100;
  String countStr = String(count);

  upperArea.ClearArea();      // 영역 지움
  // 영역의 좌우 및 상하 가운데 정렬로 문자열 표시
  upperArea.DrawString(countStr.c_str(), gTextfmt_center, gTextfmt_center);

  int reading = analogRead(A5);   // 온도 센서 읽기
  // 전압에 100을 곱하면 섭씨 온도를 얻을 수 있다.
  float temperature = reading / 1024.0 * 500;

  lowerArea.print("Temperature : ");  // 아래쪽 영역에 온도 표시
  lowerArea.print(temperature, 2);
  lowerArea.println(" C");

  delay(1000);
}
