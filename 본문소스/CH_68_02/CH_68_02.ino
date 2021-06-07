#include <WiFiEsp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(2, 3);    // ESP-01 모듈 연결 포트

void setup() {
  Serial.begin(9600);     // 컴퓨터와의 UART 시리얼 연결
  ESPSerial.begin(9600);      // ESP-01 모듈과의 UART 시리얼 연결

  WiFi.init(&ESPSerial);      // ESP-01 모듈 초기화

  listNetworks();         // AP 검색
}

void loop() { }

void listNetworks() {
  Serial.println("** 무선 네트워크를 검색합니다. **");
  byte numSsid = WiFi.scanNetworks();   // AP 검색

  Serial.print("발견된 무선 네트워크의 수 : ");
  Serial.println(numSsid);    // 검색된 AP 개수

  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.println(WiFi.SSID(thisNet));   // SSID, AP 이름
    Serial.print("\t신호 세기\t\t: ");
    Serial.print(WiFi.RSSI(thisNet));   // 신호 세기
    Serial.println(" dBm");
    Serial.print("\t암호화 방식\t: ");
    Serial.println(WiFi.encryptionType(thisNet)); // 암호화 방식
  }
}
