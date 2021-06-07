void setup() {
  Serial.begin(9600);     // 시리얼 포트 초기화

  // 정렬할 문자열 배열
  String str[5] = { "아두이노", "우노", "ATmega328", "시리얼 모니터", "String" };

  for (int i = 0; i < 4; i++) {   // 문자열을 오름차순으로 정렬
    for (int j = i + 1; j < 5; j++) {
      int compare = str[i].compareTo(str[j]);
      if (compare > 0) {
        String temp = str[i];
        str[i] = str[j];
        str[j] = temp;
      }
    }
  }

  for (int i = 0; i < 5; i++) {     // 정렬된 문자열 출력
    Serial.println(String(i) + " : " + str[i]);
  }
}

void loop() {
}
