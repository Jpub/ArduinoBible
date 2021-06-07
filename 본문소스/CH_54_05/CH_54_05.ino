#include <SD.h>

#define USING_PLOTTER      // 텍스트 메시지 출력 금지

#define SD_CS 10      // SD 카드 Chip/Slave Select
#define WRITE_INTERVAL 1000     // 30초 간격으로 측정해서 기록

const char fileName[] = "sensor.txt";
unsigned long time_previous, time_current;

void setup() {
  Serial.begin(9600);

  serialMessage("* SD 카드를 초기화합니다.");
  if (!SD.begin(SD_CS)) {     // SD 카드 초기화
    serialMessage("** 초기화 과정에서 오류가 발생했습니다.");
    while (1);
  }
  serialMessage("* 초기화를 완료했습니다.");
  serialMessage("* 온도 데이터 로깅을 시작합니다.");

  time_previous = millis();
}

void serialMessage(char *message) {
#ifndef USING_PLOTTER     // 시리얼 플로터를 사용하는 경우 
  Serial.println(message);      // 텍스트 메시지 출력 금지
#endif
}

float readTemperature() {
  int reading = analogRead(A0);

  float voltage = reading * 5.0 / 1023.0; // 전압으로 변환
  float temperature = voltage * 100;  // '전압 * 100'으로 온도 계산

  return temperature;
}

void loop() {
  time_current = millis();

  if (time_current - time_previous >= WRITE_INTERVAL) {
    time_previous = time_current;

    float temperature = readTemperature();

    // 텍스트 파일을 쓰기 모드로 열기
    File myFile = SD.open(fileName, FILE_WRITE);
    if (myFile) {
      myFile.println(temperature, 2); // SD 카드에 저장
      Serial.println(temperature, 2);   // 시리얼 모니터, 시리얼 플로터 공통

      myFile.close();     // 텍스트 파일 닫기
    }
  }
}
