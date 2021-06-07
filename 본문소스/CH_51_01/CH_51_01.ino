#include <swRTC.h>

swRTC rtc;           // swRTC 객체 생성
byte sec_previous = -1, sec_current;  // 초 단위 시간 경과 확인

void setup() {
  rtc.stopRTC();        // RTC 정지
  rtc.setTime(15, 0, 0);      // 15시 0분 0초로 설정
  rtc.setDate(1, 8, 2020);    // 2020년 8월 1일로 설정
  rtc.startRTC();       // RTC 시작

  Serial.begin(9600);       // 시리얼 통신 초기화
}

void loop() {
  sec_current = rtc.getSeconds();   // 현재 시각의 초 얻기

  if (sec_current != sec_previous) {  // 마지막 출력 후 1초 이상 경과
    sec_previous = sec_current;
    printCurrentDateTime();   // 현재 시각 출력
  }
}

void printCurrentDateTime(void) {   // 현재 날짜와 시각 출력
  Serial.print(fixedWidthStr(rtc.getYear(), 4) + "년 ");
  Serial.print(fixedWidthStr(rtc.getMonth(), 2) + "월 ");
  Serial.print(fixedWidthStr(rtc.getDay(), 2) + "일, ");

  Serial.print(fixedWidthStr(rtc.getHours(), 2) + "시 ");
  Serial.print(fixedWidthStr(rtc.getMinutes(), 2) + "분 ");
  Serial.println(fixedWidthStr(rtc.getSeconds(), 2) + "초");
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
