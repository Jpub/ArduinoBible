#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> RTC(Wire);     // DS1307 RTC 칩 객체 생성
byte sec_previous = -1, sec_current;  // 초 단위 시간 경과 확인

int pin_LED = 13;       // LED 연결 핀
boolean state = false;      // LED 상태

void blink() {        // 외부 인터럽트 서비스 루틴
  state = !state;         // LED 상태 반전
  digitalWrite(pin_LED, state);     // 현재 LED 상태 출력
}

void setup () {
  Serial.begin(9600);       // 시리얼 통신 초기화
  RTC.Begin();        // DS1307 RTC 칩 연결 초기화

  if (!RTC.GetIsRunning()) {    // RTC 동작 상태 검사
    Serial.println("* RTC가 정상적으로 동작하지 않아 재시작합니다.");
    RTC.SetIsRunning(true);     // RTC 시작
  }

  // 컴파일 시간보다 RTC 모듈의 시간이 오래된 경우 시간 업데이트
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  RtcDateTime now = RTC.GetDateTime();  // 현재 시각 얻기
  if (now < compiled) {
    Serial.println("* RTC의 시간을 업데이트 합니다.");
    RTC.SetDateTime(compiled);    // 시간 업데이트
  }

  pinMode(pin_LED, OUTPUT);     // LED 연결 핀을 출력으로 설정
  digitalWrite(pin_LED, state);     // LED 초기 상태

  RTC.Enable32kHzPin(false);    // 32.768kHz 구형파 생성 금지
  // 구형파 생성 설정
  RTC.SetSquareWavePin(DS3231SquareWavePin_ModeClock);
  // 구형파 주파수 설정
  RTC.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1Hz);

  // 디지털 2번 핀으로 입력되는 정현파의 상승 및 하강 에지에서
  // 'blink' 함수가 호출되도록 인터럽트 처리 함수 등록
  attachInterrupt(digitalPinToInterrupt(2), blink, CHANGE);
}

void loop () {
  RtcDateTime now = RTC.GetDateTime();  // 현재 시각 얻기
  sec_current = now.Second();

  if (sec_current != sec_previous) {  // 마지막 출력 후 1초 이상 경과
    sec_previous = sec_current;
    printDateTime(now);       // 시간 출력
  }
}

String fixedWidthStr(int n, int width) {  // 정수를 지정한 길이 문자열로 변환
  String str = "";

  for (int i = 0; i < width; i++) {
    int remain = n % 10;
    n = n / 10;
    str = char(remain + '0') + str;
  }

  return str;
}

void printDateTime(const RtcDateTime dt) {
  Serial.print(fixedWidthStr(dt.Year(), 4) + "년 ");
  Serial.print(fixedWidthStr(dt.Month(), 2) + "월 ");
  Serial.print(fixedWidthStr(dt.Day(), 2) + "일, ");
  Serial.print(fixedWidthStr(dt.Hour(), 2) + "시 ");
  Serial.print(fixedWidthStr(dt.Minute(), 2) + "분 ");
  Serial.println(fixedWidthStr(dt.Second(), 2) + "초");
}
