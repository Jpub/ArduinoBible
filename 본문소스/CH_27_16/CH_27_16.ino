#include <SPI.h>
#define TERMINATOR   '\n'

int count = 99;

void setup () {
  SPI.begin ();         // SPI 통신 초기화
}

void loop () {
  // 안정적인 전송을 위해 전송 속도를 1MHz로 낮춤
  SPI.beginTransaction( SPISettings(1000000, MSBFIRST, SPI_MODE0) );

  count++;            // 카운터 값 증가
  digitalWrite(SS, LOW);      // 슬레이브 선택

  char buffer[6] = "";
  sprintf(buffer, "%d", count);   // 카운터 값을 문자열로 변환
  int N = strlen(buffer);     // 문자열의 길이

  for (int i = 0; i < N; i++) {   // 바이트 단위 전송
    SPI.transfer(buffer[i]);
  }
  SPI.transfer(TERMINATOR);

  digitalWrite(SS, HIGH);       // 슬레이브 선택 해제
  SPI.endTransaction();     // 전송 종료

  delay(1000);
}
