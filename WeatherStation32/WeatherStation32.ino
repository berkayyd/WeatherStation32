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
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); // dht sensor
BlynkTimer timer;

void sendSensor() 
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP()); 
  mbar = pressure / 100; 
  visible = SI1145.ReadVisible(); // visible radiation
  ir = SI1145.ReadIR(); // IR radiation
  uv = SI1145.ReadUV(); // UV index

  Blynk.virtualWrite(V0, temperature); 
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, mbar);
  Blynk.virtualWrite(V3, visible);
  Blynk.virtualWrite(V4, ir);
  //Blynk.virtualWrite(V5, uv);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Beginning Si1145!");
  while (!SI1145.Begin())
  {
    Serial.println("Si1145 is not ready!");
    delay(1000);
  }
  Serial.println("Si1145 is ready!");
  myBarometer.init();
  dht.begin();
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  delay(1000);
  timer.setInterval(1000L, sendSensor); 
}

void loop() 
{
  Blynk.run()
  timer.run()
}