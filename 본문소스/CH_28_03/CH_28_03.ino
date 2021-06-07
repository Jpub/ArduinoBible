#define PULSE_WIDTH  5

int LOAD_PIN = 8;     // 데이터 로드
int CLOCK_PIN = 9;      // 클록
int DATA_PIN = 10;      // 데이터 입력

byte buttonValues, oldbuttonValues;

byte readButtons() {
  digitalWrite(LOAD_PIN, LOW);    // 메모리에 버튼 상태를 저장하는 단계
  delayMicroseconds(PULSE_WIDTH);
  digitalWrite(LOAD_PIN, HIGH);

  byte byteValue = 0;
  for (int i = 0; i < 8; i++) {   // H부터 A 순서로 비트 데이터 읽기
    byteValue = (byteValue << 1) | digitalRead(DATA_PIN);

    digitalWrite(CLOCK_PIN, HIGH);  // 다음 비트 읽기
    delayMicroseconds(PULSE_WIDTH);
    digitalWrite(CLOCK_PIN, LOW);
  }

  return byteValue;     // 8개 버튼 값 반환
}

void displayButtonState() {
  Serial.print("현재 버튼 상태 : ");
  for (int i = 0; i < 8; i++) {
    boolean onoff = (buttonValues >> (7 - i)) & 0x01;
    Serial.print(onoff ? "O " : ". ");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);

  pinMode(LOAD_PIN, OUTPUT);    // 데이터 로드와 클록은 출력
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, INPUT);   // 데이터 입력은 입력

  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(LOAD_PIN, HIGH);

  buttonValues = readButtons();
  displayButtonState();
  oldbuttonValues = buttonValues;
}

void loop() {
  buttonValues = readButtons();

  if (buttonValues != oldbuttonValues) {
    displayButtonState();
    oldbuttonValues = buttonValues;
  }

  delay(10);          // 디바운스
}
