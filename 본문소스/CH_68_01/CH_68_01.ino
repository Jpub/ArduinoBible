#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>

byte address[] = {192, 168, 1, 1};

void setup() {
  Serial.begin(9600);

  IPAddress ip1(192, 168, 1, 1);
  IPAddress ip2(address);
  IPAddress ip3(0xC0A80101);

  Serial.print("바이트값 4개 사용\t: ");
  Serial.println(ip1);
  Serial.print("바이트값 배열 사용\t: ");
  Serial.println(ip2);
  Serial.print("4바이트값 사용\t: ");
  Serial.println(ip3);
}

void loop() {
}
