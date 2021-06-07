#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv myTFT;

extern const uint16_t house[];
void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                   int16_t w, int16_t h, byte magX = 1, byte magY = 1);

void setup() {
  uint16_t ID = myTFT.readID();
  myTFT.begin(ID);
  myTFT.setRotation(1);

  drawRGBBitmap(0, 0, house, 80, 80, 3, 1); // x축 및 y축 방향 2배 확대
}

void loop() {
}

void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                   int16_t w, int16_t h, byte magX, byte magY) {
  for (int16_t j = 0; j < h; j++, y += magY) {
    for (int16_t i = 0; i < w; i++) {
      for (byte yy = 0; yy < magY; yy++) {
        for (byte xx = 0; xx < magX; xx++) {
          myTFT.writePixel(x + i * magX + xx, y + yy,
                           pgm_read_word(&bitmap[j * w + i]));
        }
      }
    }
  }
}
