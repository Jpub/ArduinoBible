#include <SPI.h>

void setup () {
  SPI.begin();
  Serial.begin(9600);
}

void loop () {
  if(Serial.available()){
    char ch = Serial.read();
    Serial.print(String("입력한 문자 ") + ch + " : ");
    
    if(ch == 'o' || ch == 'O'){
      send_to_slave('O');
      Serial.println("LED 켜기 명령 전송");
    }
    else if(ch == 'x' || ch == 'X'){
      send_to_slave('X');
      Serial.println("LED 끄기 명령 전송");
    }
    else{
      Serial.println("잘못된 입력");
    }
  }
}

void send_to_slave(char ch){
  // 안정적인 전송을 위해 전송 속도를 1MHz로 낮춤
  SPI.beginTransaction( SPISettings(1000000, MSBFIRST, SPI_MODE0) );
  digitalWrite(SS, LOW);      // 슬레이브 선택

  SPI.transfer(ch);

  digitalWrite(SS, HIGH);       // 슬레이브 선택 해제
  SPI.endTransaction();     // 전송 종료
}
