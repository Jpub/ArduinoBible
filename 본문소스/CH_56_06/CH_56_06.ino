const char str[] PROGMEM = "같은 문자열을 출력하고 있습니다.";

void setup() {
  Serial.begin(9600);

  Serial.println((const __FlashStringHelper *)str);
  Serial.println((const __FlashStringHelper *)str);
}

void loop() {
}
