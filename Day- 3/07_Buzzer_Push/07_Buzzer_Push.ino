// 7) WAP to turn on the buzzer for 5 seconds when user buttio is pressed.

#define BUZZER 13
#define BUTTON 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
}

int var;
void loop() {
  // put your main code here, to run repeatedly:
  var = digitalRead(BUTTON);
  Serial.println(var);
  if(var == 1)
  {
    digitalWrite(BUZZER, 1);
    Serial.println("BUZZER ON");
    delay(5000);
  }
  else
  {
    digitalWrite(BUZZER, 0);
    Serial.println("BUZZER OFF");
    //delay(1000);
  }
}
