#include <Adafruit_NeoMatrix.h>

int ROWS = 8, COLUMNS = 8;
int NUM_X = 2, NUM_Y = 1;
int PIN = 6;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
          COLUMNS, ROWS, NUM_X, NUM_Y, PIN,
          NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + 
          NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG +
          NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS);

const uint16_t textColor = matrix.Color(255, 0, 0);
int text_start = matrix.width();

void setup() {
  matrix.begin();
  matrix.setBrightness(10);

  matrix.setTextWrap(false);
  matrix.setTextColor(textColor);
}

void loop() {
  matrix.clear();
  matrix.setCursor(text_start, 0);
  matrix.print("Hello~");
  matrix.show();

  text_start--;
  if (text_start < -36) {
    text_start = matrix.width();
  }

  delay(200);
}
