int buzzerPin = 8;      // 버저 연결 핀
int BUZZER_INTERVAL = 50;

void setup () {
  pinMode(buzzerPin, OUTPUT);   // 버저 연결 핀을 출력으로 설정
}

void loop () {
  digitalWrite(buzzerPin, HIGH);    // 버저 소리 내기
  delay(BUZZER_INTERVAL);
  digitalWrite(buzzerPin, LOW);   // 버저 소리 끄기
  delay(BUZZER_INTERVAL);
}
