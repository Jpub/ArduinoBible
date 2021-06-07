int pin_button = A3;       // 버튼 누름
int pin_X = A4;         // x 축 위치
int pin_Y = A5;         // y 축 위치

void setup() {
  pinMode(pin_button, INPUT);

  Serial.begin(9600);       // 직렬 통신 초기화
}

void loop() {
  int x = analogRead(pin_X);    // X 위치
  int y = analogRead(pin_Y);    // Y 위치
  boolean press = digitalRead(pin_button);  // 버튼 누름

  Serial.print("Pressed : ");
  Serial.print(press ? "X" : "O");
  Serial.print(String(", X-position : ") + x + "\tY-position : " + y);

  delay(1000);        // 1초 대기
}
