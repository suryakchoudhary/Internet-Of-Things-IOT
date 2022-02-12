#include <WiFi.h>       //include library for wifi
#include "ThingSpeak.h"  //include library for wifi
#include "DHT.h"        //include library for DHT sensor
#include <ThingESP.h>

ThingESP32 thing("suryakant", "SmartBin", "ESP32cp-2102");

//RTC_DATA_ATTR int bootCount = 0;  // Saving data to Real Time Clock

// ULTRASONIC
#define TRIG 4
#define RECEIV 2

// DHT11_HUMIDITY_TEMPREATURE
#define DHTPIN 15 // DHT11 Data pin connected to esp32 pin no.

#define RED 21
#define GREEN 18
#define BLUE 19

// FILL LEVELS: EMPTY means maximum distance from base of dustbin to the HC-SR04
#define EMPTY 30
#define MEDIUM 20
//#define MAX 10

WiFiClient  client;

DHT dht(DHTPIN, DHT11);

unsigned long myChannelNumber = 1652835;           //channal id from thingspeak
const char * myWriteAPIKey = "CGQMNB4RTI07RHQC";   // write api kay from thingspeak
const int Fill_Level_Field1 =1;                    //channel field 1 for Level
const int Temp_Field2 =2;                          //channel field 2 for Temp.
const int Humidity_Field3 = 3;                     //channel field 3 for Humidity


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(RECEIV, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  dht.begin();
  //WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  thing.SetWiFi("Ferrari", "pawan@@0433kant");
  //thing.SetWiFi("iQOO", "surya00000kant12");
  Serial.println("\nConnected.");
  thing.initDevice();
}
/*
// ThingESP: Follows MQTT protocol and acts as BROKER to connect Twilio whatsapp API with ESP32 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
String HandleReaponse(String query) 
{
  if (query == "led on") 
  {
    digitalWrite(RED, 0);
    return "Done: LED Turned ON";
  }
  if(query == "HCSRO4 STATUS")
  return digitalRead(TRIG) ? "HCSR04 IS OFF" : "HCSR04 IS ON";

  else return "INVALID QUERY";
}*/
                                                                                       //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

void loop() 
{
  // put your main code here, to run repeatedly:

  float temperature;   // Variable to store temperature
  float humidity;      // Variable to store Humidity
  int status = 0;
  int per = 0;     // Displaying fill level percent
  int i = 0;          // Used in for loop for sending alert

  temperature = dht.readTemperature();    //read temperature
  humidity = dht.readHumidity();          //read Humidity

  // PRINTING TEMPREATURE
  Serial.println("");
  Serial.println("");
  Serial.print("TEMPREATURE: ");
  Serial.print(temperature);
  Serial.println("");
  Serial.println("");

  //CONDITION FOR SENDING HIGH TEMPREATURE ALERT
  if(temperature >= 25)
  {
    for(i=0; i<5; i++)
    {
      thing.sendMsg("+919773680338", "temperature is greater than 25 degree") ;
      delay(500);            //Minimum delay required to connect with ThingESP(500 milli seconds)
      thing.Handle();        // Handles the connection with the help of ESP32
    }
  }

  // PRINTING HUMIDITY
  Serial.print("HUMIDITY: ");
  Serial.print(humidity);
  Serial.println("");
  Serial.println("");

  //CONDITION FOR SENDING HIGH HUMIDITY ALERT
  if(humidity >= 70)
  {
    for(i=0; i<5; i++)
    {
      Serial.println();
      thing.sendMsg("+919773680338", "Humidity is greater than 70 RH") ;
      delay(500);            //Minimum delay required to connect with ThingESP(500 milli seconds)
      thing.Handle();        // Handles the connection with the help of ESP32
    }
  }


  // ULTRASONIC
  unsigned int distance = 0;
  int height = 0; 
  long duration;
  //static int count = 0;

  // MEASURING DISTANCE(ULTRASONIC_)
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(RECEIV, HIGH);
  distance = (duration * 0.034)/2;

  height = (30 - distance); // 30 is the height of the dustbin

  // FILL LEVEL

  // EMPTY
  if(height <= 10)                                 //EMPTY
  {
    digitalWrite(GREEN, HIGH);
    delay(2000);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    //status = digitalRead(GREEN);
    Serial.print("DUSTBIN IS EMPTY (GREEN_LED): ");
    Serial.print(height);
    Serial.println("cm");
    Serial.println("");
  }

  //HALF
  else if(10 < height && height <= 20)            // HALF
  {
    digitalWrite(BLUE, HIGH);
    delay(2000);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    //status = digitalRead(BLUE);
    Serial.print("DUSTBIN IS HALF FILLED (BLUE_LED): ");
    Serial.print(height);
    Serial.println("cm");
    Serial.println("");
  }

  //FULL
  else if(height > 20)                              // FULL
  {
    digitalWrite(RED, HIGH);
    delay(2000);
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    //status = digitalRead(RED);
    Serial.print("DUSTBIN IS FULL (RED_LED): ");
    Serial.print(height);
    Serial.println("cm");

    // CONDITION FOR SENDING GARBAGE FULL ALERT
    if(height > 20)
    {
      for(i=0; i<5; i++)
      {
        thing.sendMsg("+919773680338", "Dustbin Fill Level Is Greather Than 66%") ;
        delay(650);                  //Minimum delay required to connect with ThingESP(250 milli seconds)
        thing.Handle();               // Handles the connection with the help of ESP32
      }
    }
    Serial.println("");
  }

  // Percentage filled
  per = (height * 0.034) * 100;                    // 1/30 = 0.034        30cm is the height of dustbin   
  Serial.print(per);
  Serial.print("% FILLED");
  Serial.println("");
  
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

  ThingSpeak.writeField(myChannelNumber, Fill_Level_Field1, per, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, Temp_Field2, temperature, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, Humidity_Field3, humidity, myWriteAPIKey);

  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

  // DEEP SLEEP MODE
  if(height > 20)                                    // FILLED
  {
    esp_sleep_enable_timer_wakeup(2 * 1000000);   // Microsecond to second conversion factor
    Serial.println("Sleep for 2 seconds");
    esp_deep_sleep_start();  
  }
  else if(10 < height && height <= 20)                 //MEDIUM FILLED
  {
    esp_sleep_enable_timer_wakeup(4 * 1000000);   // Microsecond to second conversion factor
    Serial.println("Sleep for 4 seconds");
    esp_deep_sleep_start();
  }
  else if(height <= 10)                                  // EMPTY
  {
    esp_sleep_enable_timer_wakeup(8 * 1000000);    // Microsecond to second conversion factor
    Serial.println("Sleep for 8 seconds");
    esp_deep_sleep_start();
  }
}
