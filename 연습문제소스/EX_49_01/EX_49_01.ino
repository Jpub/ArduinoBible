#include <pitches.h>

int speakerPin = 8;
int notes[] = { 0, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };

int index_pre = 0;

void setup() {
}

void loop() {
  int a = analogRead(A0);
  int index = a / 114;

  if(index_pre != index){
    if(index == 0){
      noTone(speakerPin);
    }
    else{
      tone(speakerPin, notes[index]);
    }

    index_pre = index;
  }
}
