int pin_X = A0;        // x 축 위치
int pin_Y = A1;       // y 축 위치

void setup() {
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(pin_X);    // X 위치
  int y = analogRead(pin_Y);    // Y 위치

  Serial.print(x);
  Serial.print('\t');
  Serial.println(y);

  delay(50);
}
