class CircularStringFinder {
  private:
    byte N;           // 버퍼 크기
    byte head, tail;      // 머리, 꼬리
    char *buffer;       // 버퍼

    void clear();       // 초기화
  public:
    CircularStringFinder(byte _N);
    ~CircularStringFinder();

    void addCharacter(char ch);   // 버퍼에 문자 추가
    byte length();        // 버퍼에 저장된 문자열 길이
    void printInfo();     // 버퍼 정보 출력
};
