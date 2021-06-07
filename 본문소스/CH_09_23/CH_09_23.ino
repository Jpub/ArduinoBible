class Student {        // 클래스 정의
  public:
    String name;        // 이름 멤버 변수
    int age;            // 나이 멤버 변수
    float weight;       // 몸무게 멤버 변수
};

void setup() {
  Serial.begin(9600);

  Student student;      // Student 타입 변수 선언

  student.name = "아무개";   // 클래스의 각 멤버 변수에 변수값 대입
  student.age = 22;
  student.weight = 61.5;

  // 멤버 변수를 통한 변수값 읽기
  Serial.println(String("학생 \'") + student.name + '\'');
  Serial.println(String("\t나이는 ") + student.age + "살");
  Serial.println(String("\t몸무게는 ") + student.weight + "Kg");
}

void loop() { }
