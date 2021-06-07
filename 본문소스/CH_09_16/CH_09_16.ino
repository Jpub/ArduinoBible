void setup() {
  Serial.begin(9600);

  int array1[4];      // 초기화되지 않은 배열로 쓰레기 값 존재
  print_array(array1);

  int array2[4] = { 0, 1, 2, 3 }; // 배열 내 요소 수와 같은 수의 초깃값
  print_array(array2);

  int array3[4] = { 1 };    // 첫 번째는 1, 나머지는 0으로 초기화
  print_array(array3);

  int array4[4] = { 0 };    // 모든 요소가 0으로 초기화
  print_array(array4);
}

void print_array(int array[4]) {  // 배열 요소 출력 함수
  for (int i = 0; i < 4; i++) {
    Serial.print(array[i] + String('\t'));
  }
  Serial.println();
}

void loop() { }
