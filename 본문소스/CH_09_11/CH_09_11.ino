void setup() {
  Serial.begin(9600);

  int N1 = -7, N2 = -5, N3 = -3;
  int M1 = 3, M2 = 5, M3 = 7;

  if (N1 < N2 < N3)
    Serial.println("N2는 가운데 값입니다.");
  else
    Serial.println("N2는 가운데 값이 아닙니다.");

  if (M1 < M2 < M3)
    Serial.println("M2는 가운데 값입니다.");
  else
    Serial.println("M2는 가운데 값이 아닙니다.");
}

void loop() { }
