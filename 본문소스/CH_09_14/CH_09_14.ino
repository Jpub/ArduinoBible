void setup() {
  Serial.begin(9600);
  int count, sum;

  // do-while 문 사용
  sum = 0; count = 0;
  do {
    count++;
    sum += count;
  } while (count < 100);
  Serial.println(String("do-while 문 사용\t: ") + sum);

  // while 문 사용
  sum = 0; count = 0;
  while (count < 100) {
    count++;
    sum += count;
  }
  Serial.println(String("while 문 사용\t: ") + sum);

  // for 문 사용
  for (count = 1, sum = 0; count <= 100; count++) {
    sum += count;
  }
  Serial.println(String("for 문 사용\t: ") + sum);
}

void loop() { }
