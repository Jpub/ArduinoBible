#define NUM_OF_STR 3

char *messages[] = {
  "첫 번째 메시지입니다.",
  "두 번째 메시지는 조금 깁니다.",
  "마지막 메시지입니다."
};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_OF_STR; i++) {
    Serial.print(i + String("번 메시지 : "));
    Serial.println(messages[i]);
  }
}

void loop() {
}
