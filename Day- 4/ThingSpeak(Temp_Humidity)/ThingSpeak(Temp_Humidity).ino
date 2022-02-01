#include <WiFi.h>       //include library for wifi
#include "ThingSpeak.h"  //include library for wifi
#include "DHT.h"        //include library for DHT sensor
  //Provide your wifi details ----------------------------
char ssid[] = "Ferrari";   // your network SSID (name) 
char pass[] = "pawan@@0433kant";
 //-------------------------------------------------------
#define DHTPIN 15 // DHT11 Data pin connected to esp32 pin no.

float temperature;   // Variable to store temperature
float humidity;      // Variable to store Humidity
DHT dht(DHTPIN, DHT11);
WiFiClient  client;

unsigned long myChannelNumber = 1644803;       //channal id from thingspeak
const char * myWriteAPIKey = "6GYO8RG09WIEASKX";   // write api kay from thingspeak
const int ChannelField1 =1;   //channel field 1 for temp
const int ChannelField2 =2;   //channel field 1 for humidity   

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  dht.begin();
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
  temperature=dht.readTemperature();    //read temperature
  humidity=dht.readHumidity();          //read Humidity


  if (isnan(temperature) || isnan(humidity))
   {
     Serial.println("Failed to read from DHT sensor!\n");
     return;
     }

Serial.print("Temperature: ");
Serial.print(temperature, 1);

Serial.print(" Humidity: ");
Serial.print(humidity, 1);

ThingSpeak.writeField( myChannelNumber,ChannelField1,temperature,myWriteAPIKey);
ThingSpeak.writeField( myChannelNumber,ChannelField2,humidity,myWriteAPIKey);
}
