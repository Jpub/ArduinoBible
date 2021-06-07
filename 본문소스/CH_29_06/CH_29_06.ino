int UVsensor = A5;       // 센서 출력
int REF_3V3 = A0;       // 아두이노의 3.3V 출력 전압

byte numberOfReadings = 10;   // 평균 계산을 위한 반복 측정 횟수

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorRead = averageAnalogRead(UVsensor);
  int refRead = averageAnalogRead(REF_3V3);

  // 상대적으로 안정적인 3.3V 출력 전압을 기준으로 센서 출력 전압 계산
  float sensorVoltage = 3.3 / refRead * sensorRead;

  // 센서 출력 전압을 자외선 세기로 변환
  float uvIntensity = mapfloat(sensorVoltage, 0.99, 2.8, 0.0, 15.0);

  Serial.print("ML8511 출력 전압 : ");
  Serial.print(sensorVoltage);
  Serial.print("\t자외선 강도 (mW/cm^2) : ");
  Serial.println(uvIntensity);

  delay(5000);
}

int averageAnalogRead(int pin) {
  int averageReading = 0;

  for (int i = 0 ; i < numberOfReadings ; i++) {
    averageReading += analogRead(pin);  // 반복 측정
  }
  averageReading /= numberOfReadings; // 평균 계산

  return (averageReading);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
