const int BLUE = 22;
const int RED = 23;
const int GREEN = 21;
const int WHITE = 19;
void setup() {
  // put your setup code here, to run once:
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(WHITE, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BLUE, HIGH);
  Serial.println("BLUE ON\n");
  delay(200);

  digitalWrite(RED, HIGH);
  Serial.println("RED ON\n");
  delay(200);

  digitalWrite(GREEN, HIGH);
  Serial.println("GREEN ON\n");
  delay(200);

  digitalWrite(WHITE, HIGH);
  Serial.println("WHITE ON\n");
  delay(200);



  digitalWrite(BLUE, LOW);
  Serial.println("BLUE OFF\n");
  delay(200);

  digitalWrite(RED, LOW);
  Serial.println("RED OFF\n");
  delay(200);

  digitalWrite(GREEN, LOW);
  Serial.println("GREEN OFF\n");
  delay(200);

  digitalWrite(WHITE, LOW);
  Serial.println("WHITE OFF\n");
  delay(200);
}
