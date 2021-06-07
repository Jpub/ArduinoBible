int PIRpin = 2, LEDpin = 3;
boolean state_previous = false;

void setup() {
  pinMode(PIRpin, INPUT);
  pinMode(LEDpin, OUTPUT);

  digitalWrite(LEDpin, state_previous);

  Serial.begin(9600);
}

void loop() {
  boolean state_current = digitalRead(PIRpin);

  // 이전에 감지되지 않은 상태에서 감지된 상태로 변한 경우
  if (state_current == true) {
    if (state_previous == false) {
      Serial.println("* 어서오세요~");
      state_previous = true;
      digitalWrite(LEDpin, state_previous);
    }
  }
  // 이전에 감지된 상태에서 감지되지 않은 상태로 변한 경우
  else {
    digitalWrite(LEDpin, LOW);
    if (state_previous == true) {
      Serial.println("* 안녕히가세요~");
      state_previous = false;
    }
  }
}
