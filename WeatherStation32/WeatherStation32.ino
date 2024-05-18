#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6radUUFbx"
#define BLYNK_TEMPLATE_NAME "WeatherStation32"

#include <WiFi.h> // required libraries
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Arduino.h"
#include "DHT.h"
#include "SI114X.h"
#include "BMP085.h"
#include <Wire.h>

char auth[] = "mqxbXj-ho2-C25G-uZICtj62AgjdGd0W";
char ssid[] = "VodafoneNet-4d2a80";
char pass[] = "8U5zBmMesJ"; 

float temperature;
float humidity;
float pressure;
float mbar;
float uv;
float visible;
float ir;

SI114X SI1145 = SI114X(); // sunlight sensor
BMP085 myBarometer; // pressure sensor

#define DHTPIN 5

DHT dht(DHTPIN, DHTTYPE); // dht sensor
BlynkTimer timer;

void setup()
{

}

void loop() 
{
  Blynk.run()
  timer.run()
}