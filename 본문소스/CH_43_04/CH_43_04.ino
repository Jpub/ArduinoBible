#include <Adafruit_NeoMatrix.h>

int ROWS = 8, COLUMNS = 8;     // 네오픽셀 매트릭스 크기
int PIN = 6;

// 네오픽셀 매트릭스 제어 객체 생성
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

const uint16_t textColor = matrix.Color(255, 0, 0);
int text_start = matrix.width();    // 오른쪽에 보이지 않는 위치부터 시작

void setup() {
  matrix.begin();       // 네오픽셀 매트릭스 초기화
  matrix.setBrightness(20);     // 밝기 정도 [0 255]

  matrix.setTextWrap(false);    // 자동 줄바꿈 해제
  matrix.setTextColor(textColor);     // 문자 색상 지정
}

void loop() {
  matrix.clear();         // 모든 픽셀을 끔
  matrix.setCursor(text_start, 0);    // 커서 위치 지정
  matrix.print("Hello~");       // 문자열 출력
  matrix.show();        // 네오픽셀로 데이터 전송

  text_start--;
  if (text_start < -36) {       // 글자폭(6) * 글자수(6)
    text_start = matrix.width();    // 오른쪽 끝으로 다시 옮김
  }

  delay(200);
}
