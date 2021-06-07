volatile boolean state = false;
int pinButton = 2;
int count = 0;         // 버튼을 누른 횟수

void blink() {
  state = true;         // 버튼을 누른 상태로 바꿈
}

void setup() {
  Serial.begin(9600);       // 시리얼 통신 초기화

  // 디지털 2번 핀의 버튼이 눌러질 때 상승 에지(rising)에서
  // 'blink' 함수가 호출되도록 인터럽트 처리 루틴 등록
  attachInterrupt(digitalPinToInterrupt(pinButton), blink, RISING);
}

void loop() {
  while (!state);         // 버튼이 눌러질 때까지 대기

  count++;          // 버튼을 누른 횟수 증가
  Serial.println(String("버튼을 누른 횟수는 ") + count + "입니다.");
  state = false;        // 버튼을 누르지 않은 상태로 바꿈

  delay(50);          // 디바운싱
}
