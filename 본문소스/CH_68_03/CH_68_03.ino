#include <WiFiEsp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(2, 3);     // ESP-01 모듈 연결 포트

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 UART 시리얼 연결
  ESPSerial.begin(9600);      // ESP-01 모듈과의 UART 시리얼 연결

  WiFi.init(&ESPSerial);      // ESP-01 모듈 초기화

  String fv = WiFi.firmwareVersion();   // SDK 버전
  Serial.println("* SDK 버전 : v." + fv);
  Serial.println();

  Serial.println(String("* \'") + AP + "\'에 연결을 시도합니다.");
  status = WiFi.begin(AP, PW);

  if (status != WL_CONNECTED) {
    Serial.println("** AP에 연결할 수 없습니다.");
    while (1);
  }
  else {
    Serial.println("* AP에 연결되었습니다.");
    Serial.println();

    printCurrentNet();      // 연결된 네트워크 정보
    Serial.println();
    printWifiData();      // 무선 인터페이스 정보
  }
}

void printCurrentNet() {
  Serial.print(" >> SSID (AP 이름)\t\t: ");
  Serial.println(WiFi.SSID());

  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print(" >> BSSID (네트워크 MAC 주소)\t: ");
  printMAC(bssid);

  long rssi = WiFi.RSSI();
  Serial.print(" >> RSSI (신호 세기)\t\t: ");
  Serial.println(rssi);
}

void printWifiData() {
  IPAddress ip = WiFi.localIP();
  Serial.print(" >> IP 주소\t\t\t: ");
  Serial.println(ip);

  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print(" >> 인터페이스 MAC 주소\t\t: ");
  printMAC(mac);
}

void printMAC(byte *mac) {    // 6바이트 MAC 주소 출력
  for (int i = 5; i >= 0; i--) {
    Serial.print(mac[i], HEX);
    if (i != 0) Serial.print(":");
  }
  Serial.println();
}

void loop() {
}
