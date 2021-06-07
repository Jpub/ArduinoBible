#include <SPI.h>

unsigned int count = 99;

char transmit_data[6];      // 전송할 문자열 버퍼
volatile int transmit_count = 0;    // 전송한 분자 수
volatile boolean transmit_start = false;  // 전송 시작 여부

void setup () {
  Serial.begin(9600);

  // SPI 통신을 위한 핀들의 입출력 설정
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  // 마스터의 전송 속도에 맞추어 1MHz로 통신 속도를 설정
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  SPCR |= _BV(SPE);     // SPI 활서화
  SPCR &= ~_BV(MSTR);     // 슬레이브 모드 선택
  SPCR |= _BV(SPIE);      // 인터럽트 허용
}

// SPI 통신으로 데이터가 수신될 때 발생하는 인터럽트 처리 루틴
ISR (SPI_STC_vect) {
  uint8_t received = SPDR;    // 마스터로부터의 수신 데이터
  if (received == '$') {
    transmit_start = true;    // 데이터 전송 시작
    transmit_count = 0;
    sprintf(transmit_data, "%05d", count);  // 5자리 고정 길이 문자열로 변환
  }

  if (transmit_start) {
    if (transmit_count < 5) {   // 정수 문자열 데이터
      SPDR = transmit_data[transmit_count];
      transmit_count++;
    }
    else if (transmit_count == 5) { // 마지막 ‘#’ 문자
      SPDR = '#';
      transmit_start = false;
    }
  }
}

void loop () {
  count++;
  Serial.println(String("슬레이브 카운터 : ") + count);

  delay(1000);        // 1초에 한 번 증가
}
