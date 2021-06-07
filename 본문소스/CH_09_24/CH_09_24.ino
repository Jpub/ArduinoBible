class Student {        // 클래스 정의
  private:              // 직접 접근할 수 없는 멤버 변수
    String name;
    int age;
    float weight;
  public:             // 직접 접근할 수 있는 멤버 함수
    void setName(char *_name) {
      name = _name;
    };
    void setAge(int _age) {
      age = _age;
    };
    void setWeight(float _weight) {
      weight = _weight;
    };

    char *getName() {
      return name.c_str();
    };
    int getAge() {
      return age;
    };
    float getWeight() {
      return weight;
    };
};

void setup() {
  Serial.begin(9600);

  Student student;      // Student 타입 변수 선언

  student.setName("아무개");   // 클래스 각 멤버 변수에 변수값 대입
  student.setAge(22);
  student.setWeight(61.5);

  // 멤버 함수를 통한 변수값 읽기
  Serial.println(String("학생 \'") + student.getName() + '\'');
  Serial.println(String("\t나이는 ") + student.getAge() + "살");
  Serial.println(String("\t몸무게는 ") + student.getWeight() + "Kg");
}

void loop() { }
