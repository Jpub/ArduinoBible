#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

// 설정 변경이 MP3 플레이어 모듈에 실제 적용되기 위한 지연 시간
#define INTERNAL_DELAY   50

#define PLAYING     0x0201  // 재생 상태
#define PAUSED    0x0202  // 일시 정지 상태
#define STOPPED     0x0200  // 정지 상태

SoftwareSerial mySerial(10, 11);    // RX, TX
DFPlayerMini_Fast myMP3;    // 객체 생성

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println(F("* MP3 플레이어를 초기화합니다."));
  if (!myMP3.begin(mySerial)) {   // MP3 플레이어 초기화
    Serial.println(F(" => 초기화 과정에서 오류가 발생했습니다."));
    while (1);
  }
  Serial.println(F(" => MP3 플레이어가 연결되었습니다."));

  Serial.print(F("* SD 카드에 "));
  Serial.print(myMP3.numSdTracks());  // SD 카드 내 트랙 수 확인
  Serial.println(F("개 트랙이 있습니다."));

  myMP3.volume(10);       // 볼륨 설정 [0 30]
  myMP3.play(1);      // 첫 번째 MP3 파일 재생
  printCurrentTrackInfo();
}

void printCurrentTrackInfo() {
  delay(INTERNAL_DELAY);
  Serial.print(F(" => 현재 재생 중인 트랙은 "));
  Serial.print(myMP3.currentSdTrack()); // 현재 재생 중인 트랙 번호
  Serial.println(F("번 트랙입니다."));
}

void printVolumeInfo() {
  delay(INTERNAL_DELAY);
  Serial.print(F(" => 현재 볼륨은 "));
  Serial.print(myMP3.currentVolume());  // 현재 볼륨
  Serial.println(F("입니다."));
}

void loop() {
  if (myMP3.query(GET_STATUS) == STOPPED) {
    myMP3.playNext();     // 이전 트랙 재생이 끝난 경우
    printCurrentTrackInfo();
  }

  if (Serial.available()) {
    char ch = Serial.read();

    if (ch == '>') {      // ‘>’ 문자
      myMP3.playNext();     // 다음 트랙
      printCurrentTrackInfo();
    }
    else if (ch == '<') {     // ‘<’ 문자
      myMP3.playPrevious();   // 이전 트랙
      printCurrentTrackInfo();
    }
    else if (ch == 'U' || ch == 'u') {  // ‘U’ 또는 ‘u’ 문자
      myMP3.incVolume();    // 볼륨 크게
      printVolumeInfo();
    }
    else if (ch == 'D' || ch == 'd') {  // ‘D’ 또는 ‘d’ 문자
      myMP3.decVolume();    // 볼륨 작게
      printVolumeInfo();
    }
    else if (ch == 'P' || ch == 'p') {  // ‘P’ 또는 ‘p’ 문자
      myMP3.pause();      // 일시 정지
      Serial.println(F(" => 재생이 일시 정지되었습니다."));
    }
    else if (ch == 'R' || ch == 'r') {  // ‘R’ 또는 ‘r’ 문자
      myMP3.resume();     // 다시 재생
      Serial.println(F(" => 재생을 다시 시작합니다."));
      printCurrentTrackInfo();
    }
  }
}
