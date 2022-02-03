
#include <WiFi.h>       //include library for wifi
#include "ThingSpeak.h"  //include library for wifi
#define TRIG 4
#define RECEIV 2

char ssid[] = "Ferrari";   // your network SSID (name) 
char pass[] = "pawan@@0433kant";

WiFiClient  client;

unsigned long myChannelNumber = 1646257;       //channal id from thingspeak
const char * myWriteAPIKey = "PP5WKR0LQ3CL8QO9";   // write api kay from thingspeak
const int ChannelField1 =1;   //channel field 1 for temp
const int ChannelField2 =2;   //channel field 1 for humidity

void setup() 
  {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(TRIG, OUTPUT);
    pinMode(RECEIV, INPUT);

    WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak  
  }

void loop() 
{
  // put your main code here, to run repeatedly:

   if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
  
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print("Trying to connect\n");
      delay(2500);                             //THIS IS THE MINIMUM TIME REQUIRED TO CONNECT TO WI-FI
    } 
  }
  Serial.println("\nConnected.");

  int distance, distance1; 

  long duration;

  static int count = 0;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(RECEIV, HIGH);

  distance = (duration * 0.034)/2;

  Serial.print("DISTANCE: ");
  Serial.print(distance);
  Serial.print("\n");

  Serial.print("\n");
  delay(2000);
//------------------------------------------------------------

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(RECEIV, HIGH);
  distance1 = (duration * 0.034)/2;
  /*Serial.print("DISTANCE1: ");
  Serial.print(distance1);
  Serial.print("\n");
  Serial.print("\n");*/

  if(distance1 != distance)
  {
    count = count + 1;
    Serial.print("No. of persons:");
    Serial.print(count);
    Serial.print("\n");
  }
  delay(500);

  ThingSpeak.writeField( myChannelNumber, ChannelField1, distance, myWriteAPIKey);
  ThingSpeak.writeField( myChannelNumber, ChannelField2, count, myWriteAPIKey);

}
