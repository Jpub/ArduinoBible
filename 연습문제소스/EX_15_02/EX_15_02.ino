void setup() {
  Serial.begin(9600);

}

void loop() {
  int vr = analogRead(A0);
  byte v1, v2;
  
  if(vr >= 512){
    v1 = 255;
    v2 = (vr - 512) >> 1;

    analogWrite(5, v1);
    analogWrite(6, v2);
  }
  else{
    v1 = vr >> 1;
    v2 = 0;
    
    analogWrite(5, v1);
    analogWrite(6, v2);
  }

  Serial.println(String("( ") + v1 + " , " + v2 + " )");
  delay(500);
}
