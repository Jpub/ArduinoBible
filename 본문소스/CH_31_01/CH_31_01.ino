int triggerPin = 3;
int echoPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);    // 트리거 핀 출력으로 설정
  pinMode(echoPin, INPUT);    // 에코 핀 입력으로 설정
}

void loop() {
  digitalWrite(triggerPin, HIGH);   // 트리거 핀으로 10㎲의 펄스 발생
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // echo 핀 입력으로부터 거리를 cm 단위로 계산
  int pulseWidth = pulseIn(echoPin, HIGH);
  int distance = pulseWidth / 58;

  Serial.println("전방 장애물까지 거리 (cm) = " + String(distance));

  delay(1000);
}
