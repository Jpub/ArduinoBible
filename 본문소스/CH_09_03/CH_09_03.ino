void setup() {
  Serial.begin(9600);

  char str1[] = "ABC";      // 아스키 문자 배열
  char str2[] = "한";      // 유니 코드로 표시되는 문자

  int size = sizeof(str1);
  Serial.println(String(str1) + "\t : " + size + " bytes.");
  Serial.print("\t ");
  for (int i = 0; i < size; i++) {
    // 127보다 큰 값은 아니지만, 숫자로 출력하기 위해 byte로 변환하여 출력
    Serial.print((byte)str1[i] + String(" "));
  }
  Serial.println();

  size = sizeof(str2);
  Serial.println(String(str2) + "\t : " + size + " bytes.");
  Serial.print("\t ");
  for (int i = 0; i < size; i++) {
    // 127보다 큰 1바이트 정숫값이므로 byte로 변환하여 출력
    Serial.print((byte)str2[i] + String(" "));
  }
}

void loop() { }
