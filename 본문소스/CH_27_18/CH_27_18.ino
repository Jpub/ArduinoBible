#include <SPI.h>

#define DELAY_BETWEEN_TRANSFER_US 100  // transfer 함수 사이 시간 간격

void setup (void) {
  SPI.begin ();       // SPI 통신 초기화
  Serial.begin(9600);
}

void loop (void) {
  uint8_t from_slave;     // 슬레이브로부터의 수신 데이터
  String receive_data = "";   // 수신 데이터 버퍼

  // 안정적인 전송을 위해 전송 속도를 1MHz로 낮춤
  SPI.beginTransaction( SPISettings(1000000, MSBFIRST, SPI_MODE0) );

  digitalWrite(SS, LOW);      // 슬레이브 선택

  from_slave = SPI.transfer('$');     // 전송 시작 신호 전송
  delayMicroseconds(DELAY_BETWEEN_TRANSFER_US);
  receive_data += (char)from_slave;

  for (int pos = 0; pos < 5; pos++) {   // 5 자리 문자열로 변환된 정수 수신
    from_slave = SPI.transfer(0);
    delayMicroseconds(DELAY_BETWEEN_TRANSFER_US);
    receive_data += (char)from_slave;
  }

  digitalWrite(SS, HIGH);       // 슬레이브 선택 해제
  SPI.endTransaction();     // 전송 종료

  Serial.print("슬레이브 카운터 : [");
  Serial.print(receive_data + "] ");
  Serial.println(receive_data.substring(1).toInt());

  delay(2000);        // 2초에 한 번 요청
}
