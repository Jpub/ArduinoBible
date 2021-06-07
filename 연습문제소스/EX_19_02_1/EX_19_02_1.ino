#include <Wire.h>
#define RTC_ADDRESS 0x68    // RTC 모듈의 I2C 주소

int pin_LED = 13;     // LED 연결 핀
boolean state = false;      // LED 상태

void blink() {        // 외부 인터럽트 서비스 루틴
  state = !state;       // LED 상태 반전
  digitalWrite(pin_LED, state);   // 현재 LED 상태 출력
}

void setup() {
  Serial.begin(9600);     // UART 통신 초기화
  Wire.begin();       // I2C 초기화

  pinMode(pin_LED, OUTPUT);   // LED 연결 핀을 출력으로 설정
  digitalWrite(pin_LED, state);

  // Tiny RTC 모듈의 정현파 출력 설정
  Wire.beginTransmission(RTC_ADDRESS);  // I2C 데이터 전송 시작
  Wire.write(7);        // 7번 메모리에 데이터 기록
  Wire.write(0x10);     // 1Hz 정현파 출력
  Wire.endTransmission();   // I2C 데이터 전송 종료

  // 디지털 2번 핀으로 입력되는 정현파의 상승 및 하강 에지에서
  // ‘blink’ 함수가 호출되도록 인터럽트 처리 루틴 등록
  attachInterrupt(digitalPinToInterrupt(2), blink, RISING);
}

void loop() {
}
