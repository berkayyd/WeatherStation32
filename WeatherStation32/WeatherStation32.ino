#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6radUUFbx"
#define BLYNK_TEMPLATE_NAME "WeatherStation32"
#define BLYNK_AUTH_TOKEN "mqxbXj-ho2-C25G-uZICtj62AgjdGd0W"

#include <WiFi.h> // required libraries
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Arduino.h"
#include "DHT.h"
#include "SI114X.h"
#include "BMP085.h"
#include <Wire.h>

char ssid[] = "ssid";
char pass[] = "password"; 

float temperature;
float humidity;
float pressure;
float mbar;
float uv;
float visible;
float ir;

SI114X SI1145 = SI114X(); // sunlight sensor
BMP085 myBarometer; // pressure sensor

#define DHTPIN 4
#define DHTTYPE DHT11
#define LED_PIN 5

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

  // Convert UV to actual UV index
  float uvIndex = uv / 100.0;

  if (ir > 1500) 
  {
    Blynk.logEvent("ir_radiation");
    digitalWrite(LED_PIN, HIGH); 
  } 
  else if (uvIndex > 7.9) 
  {
    Blynk.logEvent("uv_radiation");
    digitalWrite(LED_PIN, HIGH); 
  }
  else if (temperature > 25)
  {
    Blynk.logEvent("high_temperature");
    digitalWrite(LED_PIN, HIGH); 
  }
  else 
  {
    digitalWrite(LED_PIN, LOW);
  }

  Blynk.virtualWrite(V0, temperature); 
  //Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V1, uv);
  Blynk.virtualWrite(V2, mbar);
  Blynk.virtualWrite(V3, visible);
  Blynk.virtualWrite(V4, ir);
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
  pinMode(LED_PIN, OUTPUT);
  delay(1000);

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  while (!Blynk.connected()) 
  {
    delay(1000);
    Serial.println("Connecting to Blynk...");
  }
  Serial.println("Connected to Blynk");

  timer.setInterval(1000L, sendSensor);
}

void loop() 
{
  sendSensor();
  delay(1000);
  Blynk.run();
  timer.run();
}