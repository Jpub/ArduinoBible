char TERMINATOR = '\n';
String buffer = "";
boolean process = false;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (process) {
    process = false;

    Serial.println("* 입력한 문자열 : " + buffer);

    if (buffer.equalsIgnoreCase("on")) {
      digitalWrite(13, HIGH);
      Serial.println(" => LED가 켜졌습니다.");
    }
    else if (buffer.equalsIgnoreCase("off")) {
      digitalWrite(13, LOW);
      Serial.println(" => LED가 꺼졌습니다.");
    }
    else {
      Serial.println(" => 잘못된 문자열이 입력되었습니다.");
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
