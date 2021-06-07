void setup() {
  Serial.begin(9600);

  byte n = 0xAA, m;

  Serial.print("\t\t: ");
  print_number(n);

  Serial.print("비트 단위 AND\t: ");
  m = n & 0xF0;
  print_number(m);
  Serial.print("비트 단위 OR\t: ");
  m = n | 0xF0;
  print_number(m);
  Serial.print("비트 단위 XOR\t: ");
  m = n ^ 0xF0;
  print_number(m);
  Serial.print("비트 단위 NOT\t: ");
  m = ~n;
  print_number(m);

  Serial.print("왼쪽 비트 이동\t: ");
  m = n << 2;
  print_number(m);
  Serial.print("오른쪽 비트 이동\t: ");
  m = n >> 2;
  print_number(m);
}

void print_number(byte m) {   // 16진수와 2진수로 출력
  Serial.print("0x");
  Serial.print(m, HEX);     // 16진수로 출력
  Serial.print(", 0b");
  for (int i = 7; i >= 0; i--) {    // 8자리 2진수로 출력
    if (m & (0x01 << i)) Serial.print('1');
    else Serial.print('0');
  }
  Serial.println();       // 줄바꿈
}

void loop() { }
