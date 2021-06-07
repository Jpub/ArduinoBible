#define STATE_KEY_SEARCHING     0 // 시작 문자열 탐색 중
#define STATE_VALUE_SEARCHING   1 // 값 입력 중
#define STATE_VALUE_FOUND     2 // 값 입력 종료

class CircularStringFinder {
  private:
    byte N;             // 버퍼 크기
    byte head, tail;      // 머리, 꼬리
    char *buffer;         // 버퍼

    String key;
    char terminator;
    byte search_status;

    void clear();         // 초기화
    boolean end_with_key();     // 버퍼 내용이 시작 문자열로 끝나는지 검사

  public:
    CircularStringFinder(byte _N);
    ~CircularStringFinder();

    void addCharacter(char ch);     // 버퍼에 문자 추가
    byte length();        // 버퍼에 저장된 문자열 길이
    void printInfo();       // 버퍼 정보 출력

    void setKey(String _key, char _terminator);   // 시작 문자열과 종료 문자 설정
    void restart();         // 이전 설정으로 검색 다시 시작
    String getKey();      // 시작 문자열 얻기
    char getTerminator();       // 종료 문자 얻기
    byte add(char ch);      // 버퍼에 문자 추가 및 검색
    byte getSearchStatus();     // 검색 상태 얻기
    String getValue();      // 값 얻기
};
