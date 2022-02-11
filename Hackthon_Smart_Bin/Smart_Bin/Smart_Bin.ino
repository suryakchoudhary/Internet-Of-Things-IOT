#include <WiFi.h>       //include library for wifi
#include "ThingSpeak.h"  //include library for wifi
#include "DHT.h"        //include library for DHT sensor
#include <ThingESP.h>

// ULTRASONIC
#define TRIG 4
#define RECEIV 2

// DHT11_HUMIDITY_TEMPREATURE
#define DHTPIN 15 // DHT11 Data pin connected to esp32 pin no.

#define RED 5
#define GREEN 18
#define BLUE 19

// FILL LEVELS: EMPTY means maximum distance from base of dustbin to the HC-SR04
#define EMPTY 30
#define MEDIUM 20
//#define MAX 10

// WIFI CREDENTIALS
char ssid[] = "Ferrari";   // your network SSID (name) 
char pass[] = "pawan@@0433kant";
WiFiClient  client;

DHT dht(DHTPIN, DHT11);

unsigned long myChannelNumber = 1652835;           //channal id from thingspeak
const char * myWriteAPIKey = "CGQMNB4RTI07RHQC";   // write api kay from thingspeak
const int Fill_Level_Field1 =1;                    //channel field 1 for Level
const int Temp_Field2 =2;                          //channel field 1 for Temp.
const int Humidity_Field3 = 3;                     //channel field 1 for Humidity



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

  float temperature;   // Variable to store temperature
  float humidity;      // Variable to store Humidity
  int status = 0;

  temperature = dht.readTemperature();    //read temperature
  humidity = dht.readHumidity();          //read Humidity

  // PRINTING TEMPREATURE
  Serial.print("TEMPREATURE: ");
  Serial.print(temperature);
  Serial.println("");
  Serial.println("");


  // PRINTING HUMIDITY
  Serial.print("HUMIDITY: ");
  Serial.print(humidity);
  Serial.println("");
  Serial.println("");


  // ULTRASONIC
  int distance = 0, height = 0; 
  long duration;
  static int count = 0;

  // MEASURING DISTANCE(ULTRASONIC_)
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(RECEIV, HIGH);
  distance = (duration * 0.034)/2;

  height = (40 - distance); // 40 is the hright of the dustbin

  // FILL LEVEL

  // EMPTY
  if(distance >= 30)//EMPTY)
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    //status = digitalRead(GREEN);
    Serial.print("EMPTY GREEN: ");
    Serial.print(distance);
    Serial.println("");
    Serial.println("");
  }

  //HALF
  else if(30 >= distance && distance > 20) //(MEDIUM < distance <= EMPTY)
  {
    digitalWrite(BLUE, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    //status = digitalRead(BLUE);
    Serial.print("MEDIUM BLUE: ");
    Serial.print(distance);
    Serial.println("");
    Serial.println("");
  }

  //FULL
  else if(distance <= 20)//MEDIUM)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    //status = digitalRead(RED);
    Serial.print("FILLED RED: ");
    Serial.print(distance);
    Serial.println("");
    Serial.println("");
  }
  
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

  // DEEP SLEEP MODE
  if(distance >= 20)
  {
      esp_sleep_enable_timer_wakeup(2000);
      delay(1000);
      Serial.println("Sleep for 2 seconds");
      esp_deep_sleep_start();
      Serial.println("This will never be printed");  
  }
  else if(distance < 20 && distance >30)
  {
    esp_sleep_enable_timer_wakeup(3000);
    Serial.println("Sleep for 3 seconds");
    esp_deep_sleep_start();
  }
  else if(distance < 30)
  {
    esp_sleep_enable_timer_wakeup(4000);
    Serial.println("")
  }

  delay(500);

  ThingSpeak.writeField(myChannelNumber, Fill_Level_Field1, height, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, Temp_Field2, temperature, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, Humidity_Field3, humidity, myWriteAPIKey);

}
