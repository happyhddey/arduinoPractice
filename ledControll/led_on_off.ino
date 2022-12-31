int red=10; // red led는 10번 포트
int blue=12;  // blue led는 12번 포트

void setup() {
  // blue와 red led를 연결할 포트를 OUTPUT 포트로 설정
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop() {
  // blue led를 켜고 500 대기
  digitalWrite(blue, HIGH);
  digitalWrite(red, LOW);
  delay(500);
  // red led를 켜고 500 대기
  digitalWrite(blue, LOW);
  digitalWrite(red, HIGH);
  delay(500);
}
