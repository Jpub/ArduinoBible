#define NUM_OF_STR 3

// 문자열을 플래시 메모리에서 직접 읽음
const char message1[] PROGMEM = "첫 번째 메시지입니다.";
const char message2[] PROGMEM = "두 번째 메시지는 조금 깁니다.";
const char message3[] PROGMEM = "마지막 메시지입니다.";

// 문자열에 대한 포인터를 플래시 메모리에서 직접 읽음
char *const messages[NUM_OF_STR] PROGMEM = {
  message1, message2, message3
};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_OF_STR; i++) {
    Serial.print(i + String("번 메시지 : "));
    // 플래시 메모리에 저장된 문자열에 대한 포인터 읽기
    char *ptr = (char *)pgm_read_word(&messages[i]);
    // 플래시 메모리에 저장된 문자열 출력
    Serial.println((const __FlashStringHelper *)ptr);
  }
}

void loop() {
}
