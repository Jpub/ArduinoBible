#include <OneWire.h>

OneWire iButton(2);       // 2번 핀에 iButton 연결
byte addr[8];         // 8바이트 ROM Number

void setup(void) {
  Serial.begin(9600);     // 시리얼 통신 초기화
}

void loop(void) {
  if (getKeyCode()) {     // iButton 읽기에 성공한 경우
    Serial.print("등록 번호 : ");
    for (int i = 5; i > 0; i--) {     // 시리얼 번호를 MSB부터 출력
      printTwoHexString(addr[i]);   // 16진수 두 자리로 출력
      Serial.print(' ');
    }
    Serial.print(", 패밀리 코드 : ");
    printTwoHexString(addr[0]);   // 16진수 두 자리로 출력
    Serial.println();
  }

  delay(1000);        // 1초에 한 번만 iButton 검사
}

void printTwoHexString(byte no) {   // 16진수 두 자리로 출력
  if (no < 16) {
    Serial.print('0');
  }
  Serial.print(no, HEX);
}

boolean getKeyCode() {
  if (!iButton.search(addr)) {    // 다음 1-와이어 슬레이브 검색 실패
    iButton.reset_search();   // 슬레이브 검색 초기화
    return false;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {  // 주소에 대한 CRC 검사
    Serial.println("* 주소값에 CRC 오류가 있습니다.");
    return false;
  }

  if (addr[0] != 0x01) {      // 패밀리 코드 검사
    Serial.println("* 발견된 장치는 iButton이 아닙니다.");
    return false;
  }

  return true;
}
