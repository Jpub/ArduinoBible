#include <CircularBuffer.h>

CircularBuffer<char, 5> buffer;     // char 형 5개 저장 가능한 버퍼

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {     // 4개 데이터를 버퍼에 저장
    buffer.push('A' + i);
  }
  Serial.print("초기 상태\t\t: ");
  printBuffer();
  Serial.println(String(" first 또는 head\t: ") + buffer.first());
  Serial.println(String(" last 또는 tail\t: ") + buffer.last());
  Serial.println();

  buffer.unshift('X');      // unshift : first/head에 추가
  buffer.pop();         // pop : last/tail에서 제거
  Serial.print("unshift('X'), pop() => ");
  printBuffer();

  buffer.unshift('Y');
  buffer.pop();
  Serial.print("unshift('Y'), pop() => ");
  printBuffer();

  buffer.unshift('Z');
  buffer.pop();
  Serial.print("unshift('Z'), pop() => ");
  printBuffer();
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
