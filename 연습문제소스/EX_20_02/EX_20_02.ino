#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS     2 // 온도 센서 연결 핀

OneWire oneWire(ONE_WIRE_BUS);  // OneWire 라이브러리 객체 생성
DallasTemperature sensors(&oneWire);  // 온도 센서 라이브러리 객체 생성

int deviceCount = 0;      // 연결된 온도 센서 개수
float tempC;

void setup(void) {
  Serial.begin(9600);
  sensors.begin();      // 온도 센서 라이브러리 초기화

  deviceCount = sensors.getDeviceCount();  // 연결된 온도 센서의 개수 얻기
  Serial.print(String("* ") + deviceCount);
  Serial.println("개의 온도 센서가 발견되었습니다.");
  Serial.println();
}

void loop(void) {
  sensors.requestTemperatures();  // 모든 센서의 온도 변환 시작

  for (int i = 0;  i < deviceCount;  i++) {
    Serial.print("센서 ");
    Serial.print(i + 1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i); // 배열 인덱스 기준으로 온도 얻기
    Serial.print(tempC);
    Serial.print(" C,\t");
    Serial.print(DallasTemperature::toFahrenheit(tempC)); // 화씨 변환
    Serial.println(" F");
  }

  Serial.println();
  delay(3000);
}
