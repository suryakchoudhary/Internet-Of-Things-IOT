const int LED= 22;
void setup() 
{
  // put your setup code here, to run once:
pinMode(LED,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("LED ON\n");
  delay(20); //In milli second

  digitalWrite(LED, LOW);
  Serial.println("LED OFF\n");
  delay(20);

}
