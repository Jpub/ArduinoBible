#include <Wire.h>
#define SLAVE 4

int count = 999;       // 카운터

void setup() {
  // 슬레이브 모드로 Wire 라이브러리 초기화를 위해 슬레이브 주소 지정
  Wire.begin(SLAVE);

  // 마스터의 데이터 전송 요구가 있을 때 처리할 함수 등록
  Wire.onRequest(sendToMaster);
}

void loop () {
}

void sendToMaster() {
  count++;            // 카운터 값 증가

  // 2바이트 크기의 int 타입 값을 바이트 단위로 나누어 전송
  Wire.write( (count >> 8) & 0xFF );
  Wire.write( count & 0xFF );
}
