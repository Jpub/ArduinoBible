void setup() {
  Serial.begin(9600);

  int x;
  x = -32768;
  x = x - 1;          // 언더플로 (아두이노 우노의 경우)
  Serial.println(String("-32768 - 1 = ") + x);

  x = 32767;
  x = x + 1;          // 오버플로 (아두이노 우노의 경우)
  Serial.println(String("+32767 + 1 = ") + x);
}

void loop() { }
