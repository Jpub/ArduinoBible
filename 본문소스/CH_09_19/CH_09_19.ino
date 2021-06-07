void setup() {
  Serial.begin(9600);

  int n;              // 일반 변수
  int *pn;            // 포인터 변수

  n = 3;              // 일반 변수는 값 대입
  pn = &n;          // 포인터 변수는 주소 대입

  Serial.print("일반 변수의 값\t\t\t: ");
  Serial.println(n);

  Serial.print("일반 변수가 저정된 메모리 번지\t: ");
  Serial.println(unsigned(&n), HEX);

  Serial.println();
  Serial.print("포인터 변수의 값\t\t\t: ");
  Serial.println(unsigned(pn), HEX);

  Serial.print("포인터 변수가 저장된 메모리 번지\t: ");
  Serial.println(unsigned(&pn), HEX);

  Serial.print("포인터 변수가 가리키는 메모리 값\t: ");
  Serial.println(*pn);
}

void loop() { }
