#include <OneWire.h>

OneWire DS1820(2);       // 2번 핀에 온도 센서 연결

void setup(void) {
  Serial.begin(9600);     // 시리얼 통신 초기화
}

void loop(void) {
  byte data[9];         // 스크래치 패드 데이터
  byte addr[8];         // 슬레이브 주소
  float celsius;        // 섭씨 온도

  if (!DS1820.search(addr)) {     // 다음 1-와이어 슬레이브 검색
    Serial.println("* 더 이상 1-Wire 장치가 발견되지 않았습니다.");
    Serial.println();
    DS1820.reset_search();    // 슬레이브 검색 초기화

    delay(5000);        // 5초 후 슬레이브 검색 다시 시작
    return;
  }

  Serial.print("ROM =");
  for (int i = 0; i < 8; i++) {     // 슬레이브 주소 출력
    Serial.write(' ');
    printTwoHexString(addr[i]);     // 16진수 두 자리로 출력
  }
  Serial.println();

  if (OneWire::crc8(addr, 7) != addr[7]) {  // 주소에 대한 CRC 검사
    Serial.println("* 주소값에 CRC 오류가 있습니다.");
    return;
  }

  if (addr[0] != 0x28) {      // 패밀리 코드 검사
    Serial.println("* 발견된 장치는 DS18B20 온도 센서가 아닙니다.");
    return;
  }

  DS1820.reset();       // 리셋
  DS1820.select(addr);      // 슬레이브 선택

  // 온도 변환 시작 명령
  DS1820.write(0x44);     // 외부 전력 사용
  // DS1820.write(0x44, 1);   // 기생 전력 사용

  // 12비트 온도 변환을 위해서는 750ms 이상의 시간이 필요
  delay(1000);

  DS1820.reset();       // 리셋
  DS1820.select(addr);      // 슬레이브 선택
  DS1820.write(0xBE);       // 스크래치 패드 읽기 명령

  Serial.print(" 스크래치 패드 데이터 = ");
  for (int i = 0; i < 9; i++) {     // 9바이트 스크래치 패드 데이터 읽기
    data[i] = DS1820.read();
    printTwoHexString(data[i]);   // 16진수 두 자리로 출력
    Serial.print(" ");
  }
  Serial.println();

  if (OneWire::crc8(data, 8) != data[8]) {  // 스크래치 패드 데이터에 대한 CRC 검사
    Serial.println("* 스크래치 패드 데이터에 CRC 오류가 있습니다.");
    return;
  }

  int16_t raw = (data[1] << 8) | data[0];   // 온도 레지스터 값
  // 바이트 4의 5번과 6번 비트가 해상도를 나타냄 : 0b0xx00000
  byte cfg = (data[4] & 0x60);    // 5번, 6번 비트 읽기

  if (cfg == 0x00) {
    raw = raw & 0xFFF8;   // 9 비트 해상도, 하위 3비트 제거
  } else if (cfg == 0x20) {
    raw = raw & 0xFFFC;     // 10 비트 해상도, 하위 2비트 제거
  } else if (cfg == 0x40) {
    raw = raw & 0xFFFE;     // 11 비트 해상도, 하위 1비트 제거
  }

  celsius = (float)raw / 16.0;
  Serial.println(String(" 온도는 ") + celsius + "도 입니다.");
}

void printTwoHexString(byte no) {   // 16진수 두 자리로 출력
  if (no < 16) {
    Serial.print('0');
  }
  Serial.print(no, HEX);
}
