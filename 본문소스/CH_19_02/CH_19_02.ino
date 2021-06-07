#include <Wire.h>
#define RTC_ADDRESS 0x68     // RTC 모듈의 I2C 주소

uint8_t BCD2BIN(uint8_t bcd) {    // BCD 형식 -> 이진수 형식
  return (bcd >> 4) * 10 + (bcd & 0x0F);
}

uint8_t BIN2BCD(uint8_t bin) {    // 이진수 형식 -> BCD 형식
  return ( ((bin / 10) << 4) | (bin % 10) );
}

String twoDigitString(uint8_t no) {
  return String(no / 10) + (no % 10); // 정수를 두 자리 문자열로 변환
}

void timeSetting(int _year, int _month, int _day,
                 int _hour, int _min, int _sec, int _day_of_week) {
  Wire.beginTransmission(RTC_ADDRESS); // I2C 데이터 전송 시작
  // RTC에 데이터를 기록할 메모리 시작 주소 전송
  Wire.write(0);
  // 0번지부터 기록할 7 바이트 데이터를 연속해서 전송
  Wire.write(BIN2BCD(_sec));    // 초
  Wire.write(BIN2BCD(_min));    // 분
  Wire.write(BIN2BCD(_hour));     // 시
  Wire.write(_day_of_week);     // 요일
  Wire.write(BIN2BCD(_day));    // 일
  Wire.write(BIN2BCD(_month));    // 월
  Wire.write(BIN2BCD(_year));     // 년
  Wire.endTransmission();     // I2C 데이터 전송 종료
}

void timePrint(void) {
  Wire.beginTransmission(RTC_ADDRESS);  // I2C 데이터 전송 시작
  // RTC에서 데이터를 읽어올 메모리 시작 주소 전송
  Wire.write(0);
  Wire.endTransmission();   // I2C 데이터 전송 종료

  Wire.requestFrom(RTC_ADDRESS, 7); // 7 바이트 시각 정보 요청
  while (Wire.available() == 0);    // 데이터 수신 대기

  // 0번지부터 7 바이트를 연속해서 읽어옴
  uint8_t _second = BCD2BIN(Wire.read()); // 초
  uint8_t _minute = BCD2BIN(Wire.read()); // 분
  uint8_t _hour = BCD2BIN(Wire.read()); // 시
  uint8_t _day_of_week = BCD2BIN(Wire.read());  // 요일
  uint8_t _day = BCD2BIN(Wire.read());  // 일
  uint8_t _month = BCD2BIN(Wire.read());  // 월
  uint8_t _year = BCD2BIN(Wire.read()); // 년

  // “YYYY/MM/DD, HH:MM:SS” 형식의 날짜와 시각 출력
  Serial.print("20");
  Serial.print(twoDigitString(_year));
  Serial.print('/');
  Serial.print(twoDigitString(_month));
  Serial.print('/');
  Serial.print(twoDigitString(_day));
  Serial.print(", ");
  Serial.print(twoDigitString(_hour));
  Serial.print(':');
  Serial.print(twoDigitString(_minute));
  Serial.print(':');
  Serial.println(twoDigitString(_second));
}

void setup() {
  Serial.begin(9600);       // UART 통신 초기화
  Wire.begin();         // I2C 통신 초기화
  // 2020년 2월 1일 13시 1분 30초 토요일로 초기화
  timeSetting(20, 2, 1, 13, 01, 30, 7);
}

void loop() {
  timePrint();        // 현재 시각 출력
  delay(1000);        // 1초 대기
}
