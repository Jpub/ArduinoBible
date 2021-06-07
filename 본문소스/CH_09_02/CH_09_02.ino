void setup() {
  Serial.begin(9600);

  Serial.println("bool     : " + String(sizeof(bool)));
  Serial.println("char     : " + String(sizeof(char)));
  Serial.println("byte     : " + String(sizeof(byte)));
  Serial.println("int      : " + String(sizeof(int)));
  Serial.println("word     : " + String(sizeof(word)));
  Serial.println("short    : " + String(sizeof(short)));
  Serial.println("long     : " + String(sizeof(long)));
  Serial.println("size_t   : " + String(sizeof(size_t)));
  Serial.println("uint8_t  : " + String(sizeof(uint8_t)));
  Serial.println("uint16_t : " + String(sizeof(uint16_t)));
  Serial.println("uint32_t : " + String(sizeof(uint32_t)));
  Serial.println("float    : " + String(sizeof(float)));
  Serial.println("double   : " + String(sizeof(double)));
}

void loop() { }
