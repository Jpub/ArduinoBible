void setup() {
  Serial.begin(9600);

  char c1, c2, c3, c4;

  c1 = 'C';
  c2 = c1 + 1;        // C 다음 문자
  c3 = c1 - 1;        // C 이전 문자
  c4 = c1 + 'a' - 'A';      // 대소문자 변환

  Serial.println(String("기준 문자 \t: ") + c1);
  Serial.println(String("다음 문자 \t: ") + c2);
  Serial.println(String("이전 문자 \t: ") + c3);
  Serial.println(String("대소문자 변환 \t: ") + c4);
}

void loop() { }
