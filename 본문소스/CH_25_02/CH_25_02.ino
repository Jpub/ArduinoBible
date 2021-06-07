#include <SoftwareSerial.h>

int ID = 1;           // 비콘 ID
int INTERVAL = 2000;      // 마이너 값 변경 간격, 밀리초 단위
unsigned long t_previous, t_current;

// (RX 핀, TX 핀) -> (HM-10 TX핀, HM-10 RX핀)
SoftwareSerial BLE(3, 2);

void setup() {
  BLE.begin(115200);      // HM-10 모듈과의 통신 속도
  Serial.begin(9600);       // 컴퓨터와의 통신 속도
  t_previous = millis();
}

void loop() {
  t_current = millis();

  // INTERVAL 간격에 따라 마이너 값 변경
  if (t_current - t_previous >= INTERVAL) {
    t_previous = t_current;

    int vr = analogRead(A0);
    unsigned int minor = vr + (ID << 10);

    char buffer[5] = "";
    sprintf(buffer, "%04X", minor);   // 숫자를 16진수 문자열로 변환

    Serial.println(String("* 가변저항 값 : ") + vr); // 가변저항 값 출력

    // AT 명령을 사용하여 마이너 값 변경
    BLE.println(String("AT+MINO0x") + buffer);
    Serial.println(String("AT+MINO0x") + buffer);
  }

  // 마이너 값 변경에 따른 HM-10 모듈의 출력을 시리얼 모니터로 출력
  while (BLE.available() > 0) {
    Serial.write(BLE.read());
  }
}
