int pinsLED[] = {6, 7, 8, 9, 10, 11, 12, 13};
int pinButton = 2;
boolean trigger = false;       // 버튼이 눌러진 시점 표시

unsigned long press_previous = 0, press_current;
const int MIN_INTERVAL = 50;    // 디바운싱 간격

byte pattern = 0x01;
boolean direction = true;
int INTERVAL = 1000; // 패턴이 바뀌는 시각

void reverse() { // ISR
  press_current = millis();

  if (press_current - press_previous >= MIN_INTERVAL) {
    press_previous = press_current;
    direction = !direction;
  }
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(pinsLED[i], OUTPUT);    // LED 연결 핀을 출력으로 설정
  }
  pinMode(pinButton, INPUT);    // 버튼 연결 핀을 입력으로 설정

  Serial.begin(9600);       // 시리얼 통신 초기화

  attachInterrupt(digitalPinToInterrupt(pinButton), reverse, RISING);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    boolean on_off = bitRead(pattern, i);
    digitalWrite(pinsLED[i], on_off);
  }

  delay(INTERVAL);

  if (direction) { // 왼쪽 비트 이동
    pattern = (pattern << 1) | (pattern >> 7);
  }
  else { // 오른쪽 비트 이동
    pattern = (pattern >> 1) | (pattern << 7);
  }
}
