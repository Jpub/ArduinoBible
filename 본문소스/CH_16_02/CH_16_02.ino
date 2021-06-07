#include <CircularBuffer.h>

CircularBuffer<char, 5> buffer;    // char 형 5개 저장 가능한 버퍼

void setup() {
  Serial.begin(9600);     // 시리얼 통신 초기화

  for (int i = 0; i < 4; i++) {   // 4개 데이터 버퍼에 저장
    buffer.push('A' + i);
  }
  Serial.print("초기 상태\t\t: ");
  printBuffer();
  Serial.println(String(" first 또는 head\t: ") + buffer.first());
  Serial.println(String(" last 또는 tail\t: ") + buffer.last());
  Serial.println();

  buffer.push('X');     // push : last/tail에 추가
  Serial.print("push('\X\')\t: "); printBuffer();
  buffer.push('Y');     // push : last/tail에 추가
  Serial.print("push('\Y\')\t: "); printBuffer();

  buffer.pop();       // pop : last/tail에서 제거
  Serial.print("pop()\t\t: "); printBuffer();
  buffer.pop();       // pop : last/tail에서 제거
  Serial.print("pop()\t\t: "); printBuffer();

  buffer.unshift('Z');      // unshift : first/head에 추가
  Serial.print("unshift('\Z\')\t: "); printBuffer();

  buffer.shift();       // shift : first/head에서 제거
  Serial.print("shift()\t\t: "); printBuffer();

  buffer.clear();       // clear : 모든 데이터 제거
  Serial.print("clear()\t\t: "); printBuffer();
}

void loop() {
}

void printBuffer() {
  Serial.print("[");
  if (!buffer.isEmpty()) {
    for (decltype(buffer)::index_t i = 0; i < buffer.size() - 1; i++) {
      Serial.print(buffer[i] + String(","));
    }
    Serial.print(buffer[buffer.size() - 1]);
  }
  Serial.println("]");
}
