void setup() {
}

void loop() {
  int v = analogRead(A1);
  analogWrite(1, v >> 2);
}
