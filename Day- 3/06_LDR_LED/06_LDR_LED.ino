// 6) WAP to interface LDR and turn ON/OFF thr LED based on the light intensity.

#define LDR 15
#define LED 13
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
}

int var;
void loop() {
  // put your main code here, to run repeatedly:
  var = digitalRead(LDR);
  if(var == 1)
  {
    digitalWrite(LED, 1);
    Serial.println("ON");
    delay(1000);
  }
  else
  {
    digitalWrite(LED, 0);
    Serial.println("OFF");
    delay(1000);
  }
}
