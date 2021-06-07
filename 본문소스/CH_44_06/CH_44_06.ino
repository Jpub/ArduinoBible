#include <Adafruit_STMPE610.h>

#define STMPE_CS   8   // 터치패널의 CS 핀

// 터치패널을 위한 객체 생성
Adafruit_STMPE610 myTouch = Adafruit_STMPE610(STMPE_CS);

void setup() {
  Serial.begin(9600);

  pinMode(10, OUTPUT);      // TFT-LCD가 선택되지 않도록 함
  digitalWrite(10, LOW);

  myTouch.begin();      // 터치패널 객체 초기화
}

void loop() {
  if (myTouch.touched()) {    // 터치가 발생한 경우
    TS_Point tp = myTouch.getPoint(); // 터치 정보 얻기

    Serial.print(tp.x); Serial.print('\t'); // 시리얼로 데이터 출력
    Serial.print(tp.y); Serial.print('\t');
    Serial.println(tp.z);
  }
}
