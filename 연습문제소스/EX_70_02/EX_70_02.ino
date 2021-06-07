void setup() {
  Serial.begin(9600);

  String timeString = "Sat Jan 04 08:44:11 2020";
  parseStringTime(timeString);
}

void parseStringTime(String str) {
  int year, month, day, hour, minute, second;

  char monthName[12][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  year = str.substring(20).toInt();
  String monthStr = str.substring(4, 7);
  for (int i = 0; i < 12; i++) {
    if (monthStr.equals(monthName[i])) {
      month = i + 1;
      break;
    }
  }
  day = str.substring(8, 10).toInt();
  hour = str.substring(11, 13).toInt();
  minute = str.substring(14, 16).toInt();
  second = str.substring(17, 19).toInt();

  Serial.print(year + String("년 ") + month + "월 " + day + "일, ");
  Serial.println(hour + String("시 ") + minute + "분 " + second + "초");
}

void loop() {
}
