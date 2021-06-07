void setup() {
  Serial.begin(9600);     // 시리얼 포트 초기화
}

void loop() {
}

// 수신 버퍼에 수신된 데이터가 존재하면 자동으로 호출됨
void serialEvent() {
  byte readData = Serial.read();    // 바이트 단위로 읽기
  byte writeData;

  if (readData >= 'a' && readData <= 'z') {
    writeData = readData - 'a' + 'A'; // 소문자를 대문자로 변환
  }
  else if (readData >= 'A' && readData <= 'Z') {
    writeData = readData - 'A' + 'a'; // 대문자를 소문자로 변환
  }
  else {
    writeData = readData;   // 알파벳 문자 이외에는 그대로 둠
  }

  Serial.write(writeData);      // 변환된 문자를 컴퓨터로 재전송
}
