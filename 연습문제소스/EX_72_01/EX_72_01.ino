int pinLED = 13, pinButton = 18;
boolean LED_state = false;
volatile int count = 0;
int count_previous = 0;

void blink() {
  LED_state = !LED_state;
  digitalWrite(pinLED, LED_state);

  count++;
}

void setup() {
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LED_state);

  pinMode(pinButton, INPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(pinButton), blink, RISING);
}

void loop() {
  if (count != count_previous) {
    //cli();
    count_previous = count;
    Serial.println(String("* 버튼이 ") + count + "번 눌러졌습니다.");
    //sei();
  }
}
