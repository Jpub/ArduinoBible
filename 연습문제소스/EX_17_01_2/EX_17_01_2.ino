int pin_LED = 13;
boolean state = false;
unsigned long time_previous = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin_LED, OUTPUT);
}

void loop() {
  unsigned long time_current = millis();

  if (time_current - time_previous >= 1000) {
    state = !state;
    digitalWrite(pin_LED, state);

    Serial.println(String("LED 점멸 간격은 ") + (time_current - time_previous) + "밀리초입니다.");
    time_previous = time_current;
  }
}
