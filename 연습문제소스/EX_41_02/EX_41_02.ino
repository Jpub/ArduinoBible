#include <openGLCD.h>

gText topRightArea, topLeftArea, bottomRightArea, bottomLeftArea;

int count = 0;

void setup() {
  GLCD.Init();

  topRightArea.DefineArea(textAreaTOPRIGHT);
  topRightArea.SelectFont(Verdana12);
  topRightArea.DrawString("Temp.", gTextfmt_center, gTextfmt_center);

  topLeftArea.DefineArea(textAreaTOPLEFT);
  topLeftArea.SelectFont(Verdana12);
  topLeftArea.DrawString("Count", gTextfmt_center, gTextfmt_center);

  bottomRightArea.DefineArea(textAreaBOTTOMRIGHT);
  bottomRightArea.SelectFont(Verdana12);

  bottomLeftArea.DefineArea(textAreaBOTTOMLEFT);
  bottomLeftArea.SelectFont(Verdana12);
}

void loop() {
  String str;

  // 카운트 출력
  count = (count + 1) % 100;
  str = String(count);
  bottomLeftArea.ClearArea();
  GLCD.DrawRoundRect(0, 0, 64, 64, 5);
  bottomLeftArea.DrawString(str.c_str(), gTextfmt_center, gTextfmt_center);

  // 온도 출력
  int reading = analogRead(A5);
  float temperature = reading / 1024.0 * 500;

  str = String(temperature, 2);
  str += " C";
  bottomRightArea.ClearArea();
  GLCD.DrawRoundRect(64, 0, 64, 64, 5);
  bottomRightArea.DrawString(str.c_str(), gTextfmt_center, gTextfmt_center);

  delay(1000);
}
