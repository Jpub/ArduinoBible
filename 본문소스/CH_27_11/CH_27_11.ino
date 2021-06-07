#include <Wire.h>
#define SLAVE 4

void setup() {
  // 슬레이브 모드로 Wire 라이브러리 초기화를 위해 슬레이브 주소 지정
  Wire.begin(SLAVE);
  // 마스터로부터 데이터가 전송된 경우 처리할 함수 등록
  Wire.onReceive(receiveFromMaster);

  Serial.begin(9600);
}

void loop () {
}

void receiveFromMaster(int bytes) {
  char *p = (char*)malloc(bytes + 1); // 수신 데이터를 위한 메모리 할당
  for (int i = 0; i < bytes; i++) {
    p[i] = Wire.read();       // 수신 버퍼 읽기
  }
  p[bytes] = 0;
  Serial.print(p);

  delete(p);          // 메모리 해제
}
