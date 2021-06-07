void setup() {
  Serial.begin(9600);

  int n = 10;
  if (n > 0) {
    Serial.println("양수입니다.");
  }
  else { // !(n > 0)
    // !(n > 0) && (n < 0)
    if (n < 0) {
      Serial.println("음수입니다.");
    }
    // !(n > 0) && !(n < 0)
    else {
      Serial.println("영입니다.");
    }
  }
}

void loop() { }
