int red=12;
int blue=8;

void setup() {
  Serial.begin(9600); // Serial 통신 설정
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
}

void onRed() {
  digitalWrite(red, HIGH);
}

void offRed() {
  digitalWrite(red, LOW);
}

void onBlue() {
  digitalWrite(blue, HIGH);
}

void offBlue() {
  digitalWrite(blue, LOW);
}

void wait() {
  delay(1000);
}

void loop() {

  Serial.println("Enter the color of led (R/G/P): ");
  
  // 입력이 들어올 때까지 while문에 locked -> available()은 Serial 입력이 들어오면 양수가 됨
  while (Serial.available() == 0) {}
  String s = Serial.readString();
  s.trim();  // remove any whitespace at the end of the String
  Serial.println(s);
  
  if (s == "R") {
    Serial.println("Red ON");
    onRed();
    wait();
    offRed();
  } else if (s == "B") {
    Serial.println("Blue ON");
    onBlue();
    wait();
    offBlue();
  } else if (s == "P") {
    Serial.println("Purple ON");
    onRed();
    onBlue();
    wait();
    offRed();
    offBlue();
  }
    else {
    Serial.println("Wrong Input");
  }
}
