#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv myTFT;      // TFT-LCD 제어 객체
byte r = 0;         // 회전 방향

void setup() {
  Serial.begin(9600);

  uint16_t ID = myTFT.readID();   // TFT-LCD ID 읽기
  Serial.print("* 드라이버칩\t: ILI");
  Serial.println(ID, HEX);
  myTFT.begin(ID);      // TFT-LCD 초기화
}

void loop() {
  textDemo(r);        // 텍스트 출력 데모
  r = (r + 1) % 4;      // 회전 방향 변경
  delay(3000);
}

void textDemo(byte rotation) {
  myTFT.fillScreen(TFT_WHITE);    // 화면 지우기

  Serial.println();
  Serial.print("* 화면 방향 \t\t: ");
  Serial.println(rotation);     // 화면 회전 방향
  myTFT.setRotation(rotation);    // 화면 회전

  Serial.print("* TFT-LCD 넓이 (width)\t: ");
  Serial.println(myTFT.width());    // 화면 넓이
  Serial.print("* TFT-LCD 높이 (height)\t: ");
  Serial.println(myTFT.height());   // 화면 높이

  myTFT.setTextColor(TFT_RED);
  myTFT.setTextSize(1);
  myTFT.setCursor(10, 10);
  myTFT.print("Text Size 1");

  myTFT.setTextColor(TFT_BLUE);
  myTFT.setTextSize(2);
  myTFT.setCursor(10, 18);
  myTFT.print("Text Size 2");

  myTFT.setTextColor(TFT_PURPLE);
  myTFT.setTextSize(3);
  myTFT.setCursor(10, 33);
  myTFT.print("Text Size 3");

  myTFT.setTextColor(TFT_BLACK);
  myTFT.setCursor(10, 55);
  // 화면을 넘어가는 문자열은 자동 줄바꿈이 이루어짐
  myTFT.println("MCUFRIEND_kbv class inherits from Adafruit_GFX class");
}
