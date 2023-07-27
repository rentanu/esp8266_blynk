// Robo India Tutorial
// Digital Output on LED
// Hardware: NodeMCU Blynk Board


#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6mP4Fh5I7"
#define BLYNK_TEMPLATE_NAME "MONITORING"
#define BLYNK_AUTH_TOKEN "fE0zJSzDh4XMa6zVeS_eoEcxp9-bFqcB"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"           // including the library of DHT11 temperature and humidity sensor  
#define DHTTYPE DHT11      // DHT 11

#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE);
SimpleTimer timer;
char auth[] = "fE0zJSzDh4XMa6zVeS_eoEcxp9-bFqcB";            // You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char ssid[] = "CUAN15";    // Your WiFi credentials.
char pass[] = "23572357";  // Set password to "" for open networks.
float t;                                   // Declare the variables
float h;
int ledpin = D2;
int ledpin1 = D3;


void setup()
{
  Serial.begin(9600);// Debug console
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2000, sendUptime);

  pinMode(ledpin, OUTPUT);
  pinMode(ledpin1, OUTPUT);
}



void sendUptime()
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

}

BLYNK_WRITE(V2) // Executes when the value of virtual pin 0 changes
{
  if (param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(ledpin, HIGH); // Set digital pin 2 HIGH
    //    Blynk.virtualWrite(V2,1);
    Serial.println("hidup");
  }
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(ledpin, LOW); // Set digital pin 2 LOW
    Serial.println("padam");
    //    Blynk.virtualWrite(V2,0);
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}
