char TERMINATOR = '\n';
String buffer = "";
boolean process = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (process) {
    process = false;

    int n = buffer.toInt();

    Serial.println("* 입력한 십진수 : " + buffer);
    Serial.print("  변환된 이진수 : ");
    Serial.println(n, BIN);
    buffer = "";
  }
}

void serialEvent() {
  char ch = Serial.read();

  if (ch == TERMINATOR) {
    process = true;
  }
  else {
    buffer += ch;
  }
}
