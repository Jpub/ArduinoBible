#include <LedControl.h>

// 객체 생성 (DIN, CS(LOAD), CLK, 모듈 수)
LedControl matrix = LedControl(12, 11, 10, 2);

uint16_t smile[] = {       // 사용자 정의 문자 데이터
  0x3C00, 0x4200, 0xA500, 0x8100,
  0xA500, 0x9900, 0x4200, 0x3C00
};

unsigned long time_previous;
int INTERVAL = 500;
int start_column = 0;     // 스마일 문자 표시 시작 칼럼
int increment = 1;      // 오른쪽(+1) 왼쪽(-1)으로 움직임

void setup() {
  for (int i = 0; i < 2; i++) {
    matrix.shutdown(i, false);    // 정상 동작 모드
    matrix.setIntensity(i, 5);    // 밝기 설정
    matrix.clearDisplay(i);     // LED 매트릭스 끄기
  }

  time_previous = millis();
  writeSmileData();
}

void writeSmileData() {     // 스마일 문자를 나누어서 표시
  for (int row = 0; row < 8; row++) { // 16열 매트릭스로 간주
    // 시작 칼럼만큼 비트 이동시켜 16비트 패턴을 생성
    uint16_t pattern = smile[row] >> start_column;
    // 상위 8비트와 하위 8비트로 각 모듈 데이터 생성
    byte pattern_upper = (pattern >> 8) & 0xFF;
    byte pattern_lower = pattern & 0xFF;

    matrix.setRow(0, row, pattern_upper); // 각 모듈에 표시
    matrix.setRow(1, row, pattern_lower);
  }
}

void loop() {
  unsigned long time_current = millis();

  if (time_current - time_previous >= INTERVAL) {
    time_previous = time_current;

    if (increment == 1 && start_column == 8) {
      increment = -1;     // 오른쪽 끝에 도달한 경우 방향 바꿈
    }
    else if (increment == -1 && start_column == 0) {
      increment = 1;      // 왼쪽 끝에 도달한 경우 방향 바꿈
    }

    start_column = start_column + increment;
    writeSmileData();
  }
}
