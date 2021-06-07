int pins[] = {9, 10, 11};    // LED 연결 핀
int brightness = 0;
const int GAP = 256 * 0.36;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 3; i++){
    int temp = (brightness + GAP * i) % 256;
    analogWrite(pins[i], temp);
    Serial.print(String(temp) + " ");
  }
  Serial.println();
  
  brightness = (brightness + 2) % 256;

  delay(10);
}
