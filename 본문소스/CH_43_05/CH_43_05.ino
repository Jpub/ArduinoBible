#include <Adafruit_NeoMatrix.h>

int ROWS = 8, COLUMNS = 8;     // 네오픽셀 매트릭스 크기
int PIN = 6;

// 네오픽셀 매트릭스 제어 객체 생성
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

// 열에 따라 무지개색으로 설정, 시작과 끝 열은 사용하지 않으므로 색을 지정하지 않음
uint16_t digitColor[8] = {      // 빨주노초파보
  matrix.Color(0, 0, 0),
  matrix.Color(255, 0, 0), matrix.Color(255, 127, 0), matrix.Color(255, 255, 0),
  matrix.Color(0, 255, 0), matrix.Color(0, 0, 255), matrix.Color(143, 0, 255),
  matrix.Color(0, 0, 0)
};

const uint8_t number_data[10][8] = {  // 0~9까지의 행 우선 숫자 데이터
  0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C,
  0x08, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x3C, 0x42, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7E,
  0x3C, 0x42, 0x02, 0x1C, 0x02, 0x02, 0x42, 0x3C,
  0x0C, 0x14, 0x24, 0x44, 0x7E, 0x04, 0x04, 0x04,
  0x7E, 0x40, 0x40, 0x7C, 0x02, 0x02, 0x02, 0x7C,
  0x3C, 0x42, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x3C,
  0x7E, 0x02, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
  0X3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x3C,
  0x3C, 0x42, 0x42, 0x3C, 0x04, 0x08, 0x10, 0x20
};

int index = 0;        // 표시할 숫자 인덱스

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(10);     // 밝기 정도 [0 255]
}

void loop() {
  matrix.clear();         // 모든 픽셀을 끔

  for (int r = 0; r < 8; r++) {   // drawPixel 함수로 픽셀 단위 제어
    uint8_t pattern = number_data[index][r];
    for (int c = 0; c < 8; c++) {
      // 첫 번째 열 데이터가 MSB에 저장되어 있음
      boolean pixel_on = (pattern >> (7 - c)) & 0x01;
      if (pixel_on) {
        // 켜는 픽셀일 때 열에 따라 무지개색으로 표현
        matrix.drawPixel(c, r, digitColor[c]);
      }
    }
  }
  matrix.show();        // 네오픽셀로 데이터 전송

  index = (index + 1) % 10;     // 표시할 숫자 인덱스 변경

  delay(1000);
}
