#include <EEPROM.h>
#define COUNT 1000

unsigned long time_start, time_end;

void setup() {
  Serial.begin(9600);

  time_start = millis();      // EEPROM에 쓰기
  for (int i = 0; i < COUNT; i++) EEPROM.write(i, i);
  time_end = millis();
  Serial.println(String("EEPROM 쓰기\t(ms) : ") + (time_end - time_start));

  time_start = micros();      // EEPROM에서 읽기
  for (int i = 0; i < COUNT; i++) EEPROM.read(i);
  time_end = micros();
  Serial.println(String("EEPROM 읽기\t(us) : ") + (time_end - time_start));

  byte buffer[COUNT];       // SRAM
  time_start = micros();      // SRAM에 쓰기
  for (int i = 0; i < COUNT; i++) buffer[i] = i;
  time_end = micros();
  Serial.println(String("SRAM 쓰기\t(us) : ") + (time_end - time_start));

  time_start = micros();      // SRAM에서 읽기
  for (int i = 0; i < COUNT; i++) buffer[i];
  time_end = micros();
  Serial.println(String("SRAM 읽기\t(us ): ") + (time_end - time_start));
}

void loop() {
}
