/*12) WAP for Smart Lighting using PIR and LED
  Output: a) Show the output on serial terminal.
          b) Show on the cloud dashboard (Person Count and LED Status)*/

#include <WiFi.h>
#include "ThingSpeak.h"
#define PIR 15
#define LED 13

// WI-FI DETAILS
char ssid[]= "Ferrari";
char pass[]= "pawan@@0433kant";
WiFiClient client;

// THINGSPEAK DETAIL
unsigned long channel_id = 1652249;
const char * API_Key = "7J4THVAZN1DY8W85";
const int channelfield1 = 1;
const int channelfield2 = 2;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  // CONNECTING WI-FI
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to ssid: ");
    Serial.print(ssid);
    
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.println("Trying to connect");
      delay(2500);
    }
  }
  Serial.println("CONNECTED");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int val= 0, led = 0;
  val = digitalRead(PIR);
  if(val == HIGH)
  {
    digitalWrite(LED, HIGH);
    led = digitalRead(LED);
    Serial.println("Motion Detected: ");
    Serial.println(led);
  }
  else
  {
    digitalWrite(LED, LOW);
    led = digitalRead(LED);
    Serial.println("No Motion Detected: ");
    Serial.println(led);
    
  }
  delay(500);
  ThingSpeak.writeField(channel_id, channelfield1, val, API_Key);
  ThingSpeak.writeField(channel_id, channelfield2, led, API_Key);
}
