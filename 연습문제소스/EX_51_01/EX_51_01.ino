#include <Wire.h>
#include <RtcDS1307.h>

RtcDS1307<TwoWire> RTC(Wire);    // DS1307 RTC 객체 생성

char TERMINATOR = '\n';
String buffer = "";
boolean process_it = false;

void setup () {
  Serial.begin(9600);       // 시리얼 통신 초기화
  RTC.Begin();

  if (!RTC.GetIsRunning()) {    // RTC 동작 상태 검사
    Serial.println("* RTC가 정상적으로 동작하지 않아 재시작합니다.");
    RTC.SetIsRunning(true);     // RTC 시작
  }

  // 컴파일 시간보다 RTC 모듈의 시간이 오래된 경우 시간 업데이트
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  RtcDateTime now = RTC.GetDateTime();  // 현재 시간 얻기
  if (now < compiled) {
    Serial.println("* RTC의 시간을 업데이트 합니다.");
    RTC.SetDateTime(compiled);    // 시간 업데이트
  }
}

void loop () {
  if (Serial.available()) {
    char ch = Serial.read();

    if (ch == TERMINATOR) {
      process_it = true;
    }
    else {
      buffer += ch;
    }
  }

  if (process_it) {
    Serial.print(String("\"") + buffer + "\" ");
    if (buffer.equalsIgnoreCase("now")) {
      Serial.print("* 현재 시각은 ");
      RtcDateTime now = RTC.GetDateTime();
      printDateTime(now);
    }
    else {
      Serial.println("* 잘못된 명령이 입력되었습니다.");
    }

    process_it = false;
    buffer = "";
  }
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
