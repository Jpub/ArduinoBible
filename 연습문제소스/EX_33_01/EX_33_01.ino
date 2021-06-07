#include "DHT.h"

byte pinsLED[] = {8, 9, 10};

unsigned long time_previous, time_current;
int INTERVAL = 2000;

const byte DHTPIN = 2;       // DHT11 센서가 연결된 핀
DHT dht(DHTPIN, DHT11);   // 객체 생성

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 3; i++){
    pinMode(pinsLED[i], OUTPUT);
    digitalWrite(pinsLED[i], LOW);
  }

  dht.begin();
  time_previous = millis();
}

void loop() {
  time_current = millis();

  if(time_current - time_previous >= INTERVAL){
    time_previous = time_current;
  
    float h = dht.readHumidity();
    float c = dht.readTemperature();  // 섭씨
  
    if (isnan(h) || isnan(c)) {
      Serial.println("* 온습도 데이터 읽기 실패...");
      return;
    }
  
    float index = 1.8 * c - 0.55 * (1 - h / 100) * (1.8 * c - 26) + 32;

    Serial.println(String("습도 \t: ") + h + " %");
    Serial.println(String("섭씨온도 \t: ") + c + " C");
    Serial.println(String("불쾌지수 \t: ") + index);
    
    int count = 0;
    if(index < 68) count = 0;
    else if(index < 75) count = 1;
    else if(index < 80) count = 2;
    else count = 3;

    Serial.print("\t  ");
    for(int i = 0; i < 3; i++){
      if(i < count){
        digitalWrite(pinsLED[i], HIGH);
        Serial.print("O ");
      }
      else {
        digitalWrite(pinsLED[i], LOW);
        Serial.print(". ");
      }
    }
    Serial.println();
  }
}
