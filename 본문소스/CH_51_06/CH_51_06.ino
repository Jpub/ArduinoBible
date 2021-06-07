#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> RTC(Wire);     // DS1307 RTC 칩 객체 생성
boolean interrupted = false;    // 인터럽트 발생 플래그

void handleAlarm() {      // 외부 인터럽트 서비스 루틴
  interrupted = true;     // 인터럽트 발생 표시
}

void setup () {
  Serial.begin(9600);       // 시리얼 통신 초기화
  RTC.Begin();        // DS1307 RTC 칩 연결 초기화

  RTC.Enable32kHzPin(false);    // 32.768kHz 구형파 생성 금지
  // 1번 알람을 사용하도록 설정
  RTC.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmOne);
  // 1번 알람의 알람 정보 설정
  DS3231AlarmOne alarm1(0, 0, 0, 0, DS3231AlarmOneControl_OncePerSecond);
  RTC.SetAlarmOne(alarm1);    // 알람 정보를 DS3231 RTC 칩으로 전송

  RTC.LatchAlarmsTriggeredFlags();  // 알람 발생 허용

  // 디지털 2번 핀으로 입력되는 정현파의 하강 에지에서
  // 'handleAlarm' 함수가 호출되도록 인터럽트 처리 함수 등록
  attachInterrupt(digitalPinToInterrupt(2), handleAlarm, FALLING);
}

void loop () {
  if (interrupted) {
    Serial.print("Interrupted : ");
    RtcDateTime now = RTC.GetDateTime();  // 현재 시각 얻기
    printDateTime(now);         // 시간 출력

    RTC.LatchAlarmsTriggeredFlags();    // 알람 발생 허용
    interrupted = false;        // 인터럽트 발생 플래그 클리어
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
