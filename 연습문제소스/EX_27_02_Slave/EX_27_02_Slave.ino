#include <Wire.h>
#define SLAVE 4

void setup() {
  // 슬레이브 모드로 Wire 라이브러리 초기화를 위해 슬레이브 주소 지정
  Wire.begin(SLAVE);
  // 마스터의 데이터 전송 요구가 있을 때 처리할 함수 등록
  Wire.onRequest(sendToMaster);

  Serial.begin(9600);
}

void loop () {
}

void sendToMaster() {
  int vr = analogRead(A0);

  Serial.println(vr);
  
  char buffer[5];
  sprintf(buffer, "%04d", vr);

  byte checksum = 0;
  for (int i = 0; i < 5; i++) {   // 오류 검출을 위한 체크섬 계산
    checksum = checksum ^ buffer[i];
  }

  Wire.print(buffer);
  Wire.write(checksum);
}
