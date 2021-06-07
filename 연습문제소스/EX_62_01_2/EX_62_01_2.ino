byte pins[] = {8, 9, 10, 11, 12, 13};
boolean state = true;

void setup() {
  for(byte i = 0; i < 6; i++){
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  state = !state;

  for(byte i = 0; i < 6; i++){
    digitalWrite(pins[i], state);
  }
  
  delay(1000);
}
