class Student {        // 클래스 정의
  private:              // 직접 접근할 수 없는 멤버 변수
    String name;
    int age;
    float weight;
  public:             // 연산자 오버로딩
    void operator=(const char *_name) {
      name = _name;
    };
    void operator=(const int &_age) {
      age = _age;
    };
    void operator=(const float &_weight) {
      weight = _weight;
    };

    operator char*() {
      return name.c_str();
    };
    operator int() {
      return age;
    };
    operator float() {
      return weight;
    };
};

void setup() {
  Serial.begin(9600);

  Student student;      // Student 타입 변수 선언

  student = "아무개";      // 클래스 각 멤버 변수에 변수값 대입
  student = 22;
  student = 61.5f;

  // 캐스팅에 의한 변수값 읽기
  Serial.println(String("학생 \'") + (char*)student + '\'');
  Serial.println(String("\t나이는 ") + (int)student + "살");
  Serial.println(String("\t몸무게는 ") + (float)student + "Kg");
}

void loop() { }
