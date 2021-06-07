#define NUM_OF_STR 3

// 2차원 배열을 플래시 메모리에서 직접 읽음
const char messages[NUM_OF_STR][45] PROGMEM = {
  "첫 번째 메시지입니다.",
  "두 번째 메시지는 조금 깁니다.",
  "마지막 메시지입니다."
};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_OF_STR; i++) {
    Serial.print(i + String("번 메시지 : "));
    // 플래시 메모리에 저장된 문자열 출력
    Serial.println((const __FlashStringHelper *)messages[i]);
  }
}

void loop() {
}
