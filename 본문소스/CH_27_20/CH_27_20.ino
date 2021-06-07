#include <SPI.h>
#define TERMINATOR   '\n'

int slave_SS[] = { 10, 9 };     // 슬레이브 선택 핀
byte which_one = 0;     // 슬레이브 번호

int count = 99;

void setup () {
  SPI.begin ();         // SPI 통신 초기화

  // 10번 SS 핀에 대해서는 설정 작업이 필요하지 않다.
  pinMode(slave_SS[1], OUTPUT);   // SS 핀을 출력으로 설정
  digitalWrite(slave_SS[1], HIGH);    // SS 핀으로 HIGH 출력
}

void loop () {
  which_one = (which_one + 1) % 2;  // 슬레이브 번호를 번갈아 선택

  // 안정적인 전송을 위해 전송 속도를 1MHz로 낮춤
  SPI.beginTransaction( SPISettings(1000000, MSBFIRST, SPI_MODE0) );

  count++;          // 카운터 값 증가
  digitalWrite(slave_SS[which_one], LOW); // 슬레이브 선택

  char buffer[6] = "";
  sprintf(buffer, "%d", count);     // 카운터 값을 문자열로 변환
  int N = strlen(buffer);       // 문자열의 길이

  for (int i = 0; i < N; i++) {     // 바이트 단위 전송
    SPI.transfer(buffer[i]);
  }
  SPI.transfer(TERMINATOR);

  digitalWrite(slave_SS[which_one], HIGH);  // 슬레이브 선택 해제
  SPI.endTransaction();       // 전송 종료

  delay(1000);
}
