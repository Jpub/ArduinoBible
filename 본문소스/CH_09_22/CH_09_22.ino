typedef struct {         // 구조체를 새로운 타입의 변수로 정의
  String name;        // 이름 필드
  int age;          // 나이 필드
  float weight;         // 몸무게 필드
} Student;          // 새로운 데이터 타입의 이름

void setup() {
  Serial.begin(9600);

  Student student;      // Student 타입 변수 선언

  student.name = "아무개";   // 구조체의 각 필드에 변수값 대입
  student.age = 22;
  student.weight = 61.5;

  Serial.println(String("학생 \'") + student.name + '\'');
  Serial.println(String("\t나이는 ") + student.age + "살");
  Serial.println(String("\t몸무게는 ") + student.weight + "Kg");
}

void loop() { }
