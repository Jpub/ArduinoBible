int pin_LED = 13;
boolean state = false;
unsigned long time_previous = 0;
int interval = 1000;

void setup() {
  pinMode(pin_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long time_current = millis();

  if (time_current - time_previous >= interval) {
    time_previous = time_current;

    state = !state;
    digitalWrite(pin_LED, state);

    Serial.println(String("현재 점멸 시간 간격은 ") + interval + "밀리초입니다.");

  }
  int vr = analogRead(A0);
  interval = map(vr, 0, 1023, 500, 1500);
}
