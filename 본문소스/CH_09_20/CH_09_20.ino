void setup() {
  Serial.begin(9600);

  int A = 3;

  Serial.print("(setup) 변수 A가 저장된 주소 \t\t: ");
  Serial.println(unsigned(&A), HEX);
  Serial.print("(setup) 변수 A의 값 \t\t\t: ");
  Serial.println(A);

  byValue(A);       // 값에 의한 호출
  Serial.print("(setup) 값에 의한 호출 후 A의 값 \t\t: ");
  Serial.println(A);

  byReference(&A);      // 참조에 의한 호출
  Serial.print("(setup) 참조에 의한 호출 후 A의 값 \t\t: ");
  Serial.println(A);
}

void byValue(int a) {
  // a는 지역 변수로 함수에서 반환하면 a는 사라진다.

  Serial.print("\n(byValue) 지역변수가 저장된 주소 \t\t: ");
  Serial.println(unsigned(&a), HEX);
  a = 0;              // A와 다른 주소 내의 값을 변경
}

void byReference(int *pa) {
  // pa는 지역 변수로 함수에서 반환하면 pa의 값은 사라진다.
  // 하지만 setup 함수 내 변수 A가 저장된 주소와 변수 pa의 값이 같으므로
  // 주소 pa를 통해 A의 값을 변경할 수 있다.

  Serial.print("\n(byReference) 지역변수가 가리키는 주소 \t: ");
  Serial.println(unsigned(pa), HEX);
  *pa = 0;            // A와 같은 주소 내의 값을 변경
}

void loop() { }
