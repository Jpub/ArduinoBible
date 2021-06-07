char TERMINATOR = '\n';
String buffer = "";
boolean process_it = false;

void setup() {
  Serial.begin(9600);
}

String to_binary_string(int no) {
  String bin_str = "";

  do {
    int remain = no % 2;
    bin_str = remain + bin_str;
    no /= 2;
  } while (no > 0);

  return bin_str;
}

void loop() {
  while (Serial.available() > 0) {
    char ch = Serial.read();

    if (ch == TERMINATOR) {
      process_it = true;
    }
    else {
      buffer = buffer + ch;
    }
  }

  if (process_it) {
    int no = buffer.toInt();
    String bin_str = to_binary_string(no);

    Serial.print(String("입력한 숫자 ") + no + "에 해당하는 이진수는 0b");
    Serial.println(bin_str + "입니다.");

    process_it = false;
    buffer = "";
  }
}
