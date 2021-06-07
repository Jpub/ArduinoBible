char TERMINATOR = '\n';
String buffer = "";
boolean process = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (process) {
    process = false;

    Serial.println("* 입력한 숫자열 : " + buffer);

    int index_start = 0, index_current = -1;

    while (true) {
      index_current = buffer.indexOf(',', index_current + 1);
      if (index_current != -1) {
        String str = buffer.substring(index_start, index_current);
        str.trim();
        Serial.println("  : " + str);

        index_start = index_current + 1;
      }
      else {
        String str = buffer.substring(index_start);
        str.trim();
        Serial.println("  : " + str);
        break;
      }
    }
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
