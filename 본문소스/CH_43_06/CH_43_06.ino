#include <Adafruit_NeoMatrix.h>

int ROWS = 8, COLUMNS = 8;    // 네오픽셀 매트릭스 크기
int PIN = 6;

// 네오픽셀 매트릭스 제어 객체 생성
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

const uint16_t dotColor[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

const uint8_t PROGMEM user_bmp[][8] = {     // 플래시 메모리 활용
  { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C },   // 스마일
  { 0x3C, 0x42, 0xA5, 0x81, 0xBD, 0x81, 0x42, 0x3C },   // 무표정
  { 0x3C, 0x42, 0xA5, 0x81, 0x99, 0xA5, 0x42, 0x3C }
};   // 화남

int index = 0;        // 비트맵 인덱스

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(20);     // 밝기 정도 [0 255]
}

void loop() {
  matrix.clear();         // 모든 픽셀을 끔
  // 사용자 정의 비트맵 표시 (x, y, data, width, height, color)
  matrix.drawBitmap(0, 0, user_bmp[index], 8, 8, dotColor[index]);
  matrix.show();        // 네오픽셀로 데이터 전송

  index = (index + 1) % 3;    // 사용자 정의 비트맵 인덱스 변경

  delay(1000);
}
