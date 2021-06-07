struct {
  uint8_t buttons;
  int8_t x;
  int8_t y;
  int8_t wheel;
} mouseReport;

int8_t OFFSET = 50, SPACE = 10;
int INTERVAL = 1000;

void setup() {
  Serial.begin(9600);

  mouseReport.buttons = 0;
  mouseReport.x = 0;
  mouseReport.y = 0;
  mouseReport.wheel = 0;
}

void loop() {
  delay(INTERVAL * 5);

  mouseReport.buttons = 0x01;
  mouseReport.x = 0;
  mouseReport.y = 0;
  Serial.write((uint8_t *)&mouseReport, 4);   // 버튼 누름

  mouseReport.x = OFFSET;
  mouseReport.y = 0;
  Serial.write((uint8_t *)&mouseReport, 4);   // 윗쪽
  delay(INTERVAL);

  mouseReport.x = 0;
  mouseReport.y = OFFSET;
  Serial.write((uint8_t *)&mouseReport, 4);   // 오른쪽
  delay(INTERVAL);

  mouseReport.x = -OFFSET;
  mouseReport.y = 0;
  Serial.write((uint8_t *)&mouseReport, 4);   // 아랫쪽
  delay(INTERVAL);

  mouseReport.x = 0;
  mouseReport.y = -OFFSET;
  Serial.write((uint8_t *)&mouseReport, 4);   // 왼쪽

  mouseReport.buttons = 0x00;
  mouseReport.x = 0;
  mouseReport.y = 0;
  Serial.write((uint8_t *)&mouseReport, 4);   // 마우스 버튼 뗌

  mouseReport.x = SPACE;
  mouseReport.y = SPACE;
  Serial.write((uint8_t *)&mouseReport, 4);   // 그릴 위치 옮김
}
