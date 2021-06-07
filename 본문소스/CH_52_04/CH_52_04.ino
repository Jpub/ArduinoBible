int pinLED = 13, pinButton = 2;
boolean LED_state = false;
boolean trigger = false;       // 버튼이 눌러진 시점 표시
int count = 0;        // 버튼을 누른 횟수

void blink() {        // ISR
  trigger = true;       // 버튼이 눌러졌음
}

void setup() {
  pinMode(pinLED, OUTPUT);    // LED 연결 핀을 출력으로 설정
  digitalWrite(pinLED, LED_state);

  pinMode(pinButton, INPUT);    // 버튼 연결 핀을 입력으로 설정

  Serial.begin(9600);       // 시리얼 통신 초기화

  // 디지털 2번 핀의 버튼이 눌러질 때 상승 에지(rising)에서
  // 'blink' 함수가 호출되도록 인터럽트 처리 루틴 등록
  attachInterrupt(digitalPinToInterrupt(pinButton), blink, RISING);
}

void loop() {
  if (trigger) {        // 상승 에지 발생
    trigger = false;      // 버튼이 눌러진 표시 해제

    LED_state = !LED_state;     // LED 상태 반전
    digitalWrite(pinLED, LED_state);

    count++;
    Serial.println(String("* 버튼이 ") + count + "번 눌러졌습니다.");
  }
}
