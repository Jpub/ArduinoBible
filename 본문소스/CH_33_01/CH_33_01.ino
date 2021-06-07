#include <DHT.h>

const byte DHTPIN = 2;       // DHT11 센서가 연결된 핀
DHT dht(DHTPIN, DHT11);   // 객체 생성

void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  delay(2000);        // 2초 이상의 시간 간격을 둔 읽기 추천

  float h = dht.readHumidity();
  float c = dht.readTemperature();  // 섭씨 온도, 디폴트값
  float f = dht.readTemperature(true);  // 화씨 온도

  if (isnan(h) || isnan(c) || isnan(f)) {
    Serial.println("* 온도 및 습도 데이터 읽기 실패...");
    return;
  }

  Serial.println(String("습도 \t: ") + h + " %");
  Serial.println(String("섭씨온도 \t: ") + c + " C");
  Serial.println(String("화씨온도 \t: ") + f + " F");

  Serial.println();
}
