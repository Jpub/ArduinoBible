#include <Wire.h>
#define SLAVE1 4
#define SLAVE2 5

void setup() {
  // 슬레이브 모드로 Wire 라이브러리 초기화를 위해 슬레이브 주소 지정
  // 슬레이브에 따라 SLAVE1 또는 SLAVE2를 선택해서 서로 다른 주소로 지정
  Wire.begin(SLAVE1);
  // 마스터로부터 데이터가 전송된 경우 처리할 함수 등록
  Wire.onReceive(receiveFromMaster);

  Serial.begin(9600);
}

void loop () {
}

void receiveFromMaster(int bytes) {
  Serial.print("마스터 카운터 : ");

  for (int i = 0; i < bytes; i++) {
    char ch = Wire.read();
    Serial.print(ch);       // 수신 버퍼 읽기
  }
}
