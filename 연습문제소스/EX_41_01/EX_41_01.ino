#include <openGLCD.h>

void setup() {
  GLCD.Init();
  GLCD.SelectFont(cp437font8x8);
}

void loop() {
  for (int c = 0; c < 256; c++) {
    if (c == '\n' || c == '\r') {
      GLCD.print(' ');
    }else{
      GLCD.print((char)c);
    }

    if ((c + 1) % 128 == 0){
      delay(5000);
      GLCD.ClearScreen();
    }
  }
}
