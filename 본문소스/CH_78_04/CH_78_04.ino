#include <ESP8266WiFi.h>

char *ssid = "your_AP_name";
char *password = "password_to_your_AP";

void setup() {
  Serial.begin(9600);

  Serial.println();
  WiFi.mode(WIFI_STA);      // 스테이션 모드
  WiFi.disconnect();      // 기존 연결 종료

  Serial.print(String("* \'") + ssid + "\'에 연결을 시작합니다.");
  WiFi.begin(ssid, password);     // AP에 접속

  // AP에 접속이 될 때까지 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("* AP에 연결되었습니다.");

  // AP 정보
  Serial.println();
  Serial.println("* AP 정보");
  Serial.print(" - SSID\t: ");    // AP의 SSID (이름)
  Serial.println(WiFi.SSID());
  Serial.print(" - RSSI\t: ");    // AP의 신호 강도
  Serial.println(WiFi.RSSI());
  Serial.print(" - BSSID\t: ");     // AP의 MAC 주소
  printBSSID();
  Serial.print(" - Subnet mask\t: ");   // 서브넷 마스크
  Serial.println(WiFi.subnetMask());
  Serial.print(" - Gateway IP\t: ");  // 게이트웨이 주소
  Serial.println(WiFi.gatewayIP());
  Serial.print(" - DNS IP\t: ");    // DNS 주소
  Serial.println(WiFi.dnsIP());

  // 스테이션 정보
  Serial.println();
  Serial.println("* 스테이션 정보");
  Serial.print(" - IP address\t: ");  // DHCH를 통해 할당된 IP 주소
  Serial.println(WiFi.localIP());
  Serial.print(" - MAC address\t: ");   // ESP8266의 MAC 주소
  Serial.println(WiFi.macAddress());
}

void printBSSID() {       // 6바이트 MAC 주소 표시
  uint8_t *bssid = WiFi.BSSID();

  for (int i = 0; i < 6; i++) {
    Serial.print(bssid[i], HEX);
    if (i != 5) {
      Serial.print(":");
    }
  }
  Serial.println();
}

void loop() {
}
