#include <SPI.h>

volatile char ch;
boolean process_it = false;

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

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

ISR (SPI_STC_vect) {
  ch = SPDR;
  process_it = true;
}

void loop () {
  if (process_it) {
    process_it = false;
    if(ch == 'O'){
      digitalWrite(13, HIGH);
      Serial.println("LED를 켭니다.");
    }
    else if(ch == 'X'){
      digitalWrite(13, LOW);
      Serial.println("LED를 끕니다.");
    }
    else{
      Serial.println("잘못된 명령이 전달되었습니다.");
    }
  }
}
