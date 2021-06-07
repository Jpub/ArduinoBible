const int COUNT = 20;       // 이동 평균을 위한 샘플 수
int INTERVAL = 10000;       // 측정 간격
int POWER_PIN = 2;      // 전원 공급 핀
int SENSOR_PIN = A4;      // 센서 여 SRUF VLS

int buffer[COUNT] = {0, };    // 샘플 버퍼
int index = 0;        // 샘플 저장 인덱스
float sum;            // 샘플의 합

void setup() {
  Serial.begin(9600);

  pinMode(POWER_PIN, OUTPUT);   // 전원 공급 핀을 출력으로 설정
  digitalWrite(POWER_PIN, LOW);   // 전원을 공급하지 않는 상태

  sum = 0;
  for (int i = 0; i < COUNT; i++) { // 시작 샘플은 연속으로 측정
    buffer[i] = readMoisture();
    sum += buffer[i];     // 시작 샘플의 합
  }
}

void loop() {
  int reading = readMoisture();     // 샘플 읽기

  sum = sum - buffer[index];    // 이전 샘플 값을 합에서 제거
  buffer[index] = reading;    // 새로운 샘플 값 저장
  sum = sum + buffer[index];    // 새로운 샘플 값을 합에 추가
  float average = sum / COUNT;  // 샘플의 이동 평균

  index = (index + 1) % COUNT;    // 샘플 저장 위치 변경

  Serial.print(String(reading) + '\t');   // 측정값 출력
  Serial.println(average);    // 이동 평균값 출력

  delay(INTERVAL);
}

int readMoisture() {
  digitalWrite(POWER_PIN, HIGH);    // 전원 공급 시작
  delay(10);          // 전원 안정화 대기
  int ad = analogRead(SENSOR_PIN);  // 센서 읽기
  digitalWrite(POWER_PIN, LOW);   // 전원 공급 중단

  return ad;
}
