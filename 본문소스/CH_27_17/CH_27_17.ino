#include <SPI.h>
#define TERMINATOR   '\n'

char buffer[10] = "";       // 수신된 문자 저장을 위한 버퍼
volatile int pos = 0;       // 버퍼 내 저장 위치
volatile boolean process_it;    // 시리얼 모니터로 수신 내용 출력 여부

void setup () {
  Serial.begin (9600);

  // SPI 통신을 위한 핀들의 입출력 설정
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  // 마스터의 전송 속도에 맞추어 1MHz로 통신 속도를 설정
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  // SPI 통신을 위한 레지스터를 설정
  SPCR |= (1 << SPE);       // SPI 활성화
  SPCR &= ~(1 << MSTR);     // Slave 모드 선택
  SPCR |= (1 << SPIE);      // 인터럽트 허용

  process_it = false;
}

// SPI 통신으로 데이터가 수신될 때 발생하는 인터럽트 처리 루틴
ISR (SPI_STC_vect) {
  byte c = SPDR;      // 수신된 데이터

  if (c == TERMINATOR) {    // 개행문자를 수신한 경우
    buffer[pos] = 0;      // 문자열 끝 표시
    process_it = true;      // 시리얼 모니터로 출력
  }
  else {              // 개행문자 이외의 문자를 수신한 경우
    buffer[pos] = c;      // 버퍼에 저장
    pos++;
  }
}

void loop () {
  // 개행문자를 수신하여 지금까지의 수신 내용을 시리얼 모니터로 출력
  if (process_it) {
    Serial.print("마스터 카운터 : ");
    Serial.println(buffer);
    process_it = false;
    pos = 0;
  }
}
