#include <Adafruit_NeoMatrix.h>

int ROWS = 8, COLUMNS = 8;     // 네오픽셀 매트릭스 크기
int NUM_X = 2, NUM_Y = 1;   // x 및 y 방향으로 연결된 매트릭스 수
int PIN = 6;

// 두 개의 연결된 네오픽셀 매트릭스 제어 객체 생성
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
                              COLUMNS, ROWS, NUM_X, NUM_Y, PIN,
                              NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                              NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG +
                              NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS);

const uint16_t textColor = matrix.Color(255, 0, 0);

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(5);    // 밝기 정도 [0 255]

  matrix.setTextWrap(false);    // 자동 줄바꿈 해제
  matrix.setTextColor(textColor);     // 문자 색상 지정

  matrix.setCursor(0, 0);       // 커서 위치 지정

  matrix.print("Hello");      // 문자열 출력
  matrix.show();        // 네오픽셀로 데이터 전송
}

void loop() {
}
