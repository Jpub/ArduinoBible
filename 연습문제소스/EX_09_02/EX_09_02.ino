void setup() {
  Serial.begin(9600);

  prime_factorization(60);
}

void prime_factorization(int n) {
  Serial.println(String(n) + "을/를 소인수분해 하면,");

  int prime = 2;

  while(n > 1){
    if(n % prime == 0){
      Serial.println(String(" ") + prime);
      n /= prime;
    }
    else{
      prime++;
    }
  }
  Serial.println("의 소수(prime number) 곱으로 나타낼 수 있습니다.");
}

void loop() {
}
