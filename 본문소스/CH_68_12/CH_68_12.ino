#include <WiFiEsp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(2, 3);     // ESP-01 모듈 연결 포트

char AP[] = "your_AP_name_here";
char PW[] = "your_AP_password_here";

WiFiEspServer server(80);

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 UART 시리얼 연결
  ESPSerial.begin(9600);      // ESP-01 모듈과의 UART 시리얼 연결

  WiFi.init(&ESPSerial);      // ESP-01 모듈 초기화
  Serial.println(String("* \'") + AP + "\'에 연결을 시도합니다.");
  int status = WiFi.begin(AP, PW);

  if (status != WL_CONNECTED) {
    Serial.println("** AP에 연결할 수 없습니다.");
  }
  else {
    Serial.println("* AP에 연결되었습니다.");
  }
  Serial.println();

  server.begin();       // 서버 시작
  Serial.println(F("* 서버를 시작합니다."));

  IPAddress ip = WiFi.localIP();    // 서버 IP 주소 출력
  Serial.print(" => 서버 IP 주소\t: ");
  Serial.println(ip);
  Serial.println();
}

float readTemperature() {
  int reading = analogRead(A0);

  float voltage = reading * 5.0 / 1023.0;   // 전압으로 변환
  float temperature = voltage * 100;    // '전압 * 100'으로 온도 계산

  return temperature;
}

void sendResponse(WiFiEspClient client) {
  Serial.println(F("* 클라이언트로 온도 정보를 보냅니다."));

  String temperature = String(readTemperature(), 2);

  // 헤더
  client.print("HTTP/1.1 200 OK\r\n");
  client.print("Content-Type: text/html\r\n");
  client.print("Connection:close\r\n");
  client.print("\r\n");

  // 데이터
  client.print("<!DOCTYPE HTML>\r\n");
  client.print("<html>\r\n");
  client.print("Temperature : ");
  client.print(temperature);
  client.print(" C\r\n");
  client.print("</html>\r\n");
  client.print("\r\n");
}

void loop() {
  WiFiEspClient client = server.available();
  if (client) {         // 클라이언트 연결
    Serial.println(F("* 새로운 클라이언트가 연결되었습니다."));

    int line_length = 0;

    while (client.connected()) {    // 클라이언트가 연결된 동안
      if (client.available()) {   // 데이터 수신
        char ch = client.read();
        line_length++;

        if (ch == '\n') {     // 문장의 끝
          if (line_length == 2) {   // 빈 문장, 즉 마지막 문장인 경우
            sendResponse(client);   // HTTP 응답 전송

            Serial.println(F("* 클라이언트와의 연결을 종료합니다."));
            Serial.println();
            client.stop();      // 클라이언트와의 연결 종료
          }
          else {
            line_length = 0;    // 다른 헤더 문장은 처리하지 않음
          }
        }
      }
    }
  }
}
