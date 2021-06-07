void setup() {
  Serial.begin(9600);

  int n[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.print(String("n[") + i + "][" + j + "] = " + n[i][j]);
      Serial.print(String("이고, 저장되는 메모리 주소는 0x"));
      Serial.print(unsigned(&n[i][j]), HEX);
      Serial.println("입니다.");
    }
  }
}

void loop() { }
