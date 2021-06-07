#include <Wire.h>
#include <RtcDS3231.h>
#include <LowPower.h>

#define interruptPin 2      // RTC의 알람에 의한 인터럽트 발생 핀

RtcDS3231<TwoWire> RTC(Wire);     // DS1307 RTC 칩 객체 생성

void wakeUp() {
  Serial.println("* 인터럽트가 발생해서 슬립 모드에서 깨어납니다.");
  detachInterrupt(digitalPinToInterrupt(interruptPin));
}

void setup () {
  Serial.begin(9600);
  RTC.Begin();        // DS1307 RTC 칩 연결 초기화

  RTC.Enable32kHzPin(false);    // 32.768kHz 구형파 생성 금지
  // 1번 알람을 사용하도록 설정
  RTC.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmOne);
  // 1분에 1번, 30초가 될 때 알람 발생
  DS3231AlarmOne alarm1(0, 0, 0, 30, DS3231AlarmOneControl_SecondsMatch);
  RTC.SetAlarmOne(alarm1);    // 알람 정보를 DS3231 RTC 칩으로 전송
}

void loop () {
  Serial.println("* 5초 후에 슬립 모드에 들어갑니다.");
  Serial.print(" => ");
  for (byte i = 0; i < 5; i++) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println("\n* 슬립 모드에 들어갑니다.");
  Serial.println(" => RTC에 의해 매 30초에 깨어납니다.");
  delay(100);         // 시리얼 출력 완료 대기
  RTC.LatchAlarmsTriggeredFlags();  // 알람 발생 허용

  goToSleep();        // 슬립 모드 시작
}

void goToSleep() {
  attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUp, LOW);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  Serial.println(" => 슬립 모드에서 깨어났습니다.");
  Serial.print(" => 현재 시간 : ");
  RtcDateTime now = RTC.GetDateTime(); // 현재 시각 얻기
  printDateTime(now);       // 시간 출력
  Serial.println();
}

void printDateTime(const RtcDateTime dt) {
  Serial.print(fixedWidthStr(dt.Year(), 4) + "년 ");
  Serial.print(fixedWidthStr(dt.Month(), 2) + "월 ");
  Serial.print(fixedWidthStr(dt.Day(), 2) + "일, ");
  Serial.print(fixedWidthStr(dt.Hour(), 2) + "시 ");
  Serial.print(fixedWidthStr(dt.Minute(), 2) + "분 ");
  Serial.println(fixedWidthStr(dt.Second(), 2) + "초");
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
