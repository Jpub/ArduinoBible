void setup() {
  Serial.begin(9600);       // 시리얼 포트 초기화

  String str = "ABCDEFACABabAB";  // 원본 문자열
  String searchStr = "AB";    // 탐색 문자열
  int index = -1;       // 탐색 시작 위치
  int findCount = 0;      // 탐색 문자열 발견 횟수

  while (true) {
    // 검색 시작 위치를 바꾸면서 문자열 끝에 도달할 때까지 검색
    index = str.indexOf(searchStr, index + 1);
    if (index != -1) {      // 탐색 문자열 발견
      findCount++;      // 발견 횟수 증가
      Serial.println(String(findCount) + "번째 탐색 문자열 발견 위치 : " + index);
    }
    else {          // 탐색 문자열 발견되지 않음
      Serial.println("* 더이상 탐색 문자열이 존재하지 않습니다.");
      break;
    }
  }
}

void loop() {
}
