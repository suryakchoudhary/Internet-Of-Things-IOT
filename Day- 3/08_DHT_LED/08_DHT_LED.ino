// 8) WAP to interface T/RH sensor and monitor the room tempteature and indicate using appropriate color LED.

#include "DHT.h"
#define TEMP_RED 15
#define HUM_GREEN 2
#define NO_DATA_WHITE 12
#define SENSE 13
float var_t, var_h;
DHT dht(SENSE, DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TEMP_RED, OUTPUT);
  pinMode(HUM_GREEN, OUTPUT);
  pinMode(NO_DATA_WHITE, OUTPUT);
  pinMode(SENSE, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  var_h = dht.readHumidity();
  var_t = dht.readTemperature();
  

  if(var_t > 1)
  {
    digitalWrite(TEMP_RED, 1);
    digitalWrite(NO_DATA_WHITE, 0);
    Serial.println("Read_Temp\n");
    delay(1000);
  }
  else if(var_h > 1)
  {
    digitalWrite(HUM_GREEN, 1);
    digitalWrite(NO_DATA_WHITE, 0);
    Serial.println("READ_HUMIDITY\n");
    delay(1000);
  }
  else
  {
    digitalWrite(NO_DATA_WHITE, 1);
    digitalWrite(TEMP_RED, 0);
    digitalWrite(HUM_GREEN, 0);
    Serial.println("READ_Nothing\n");
    delay(1000);
  }

}
