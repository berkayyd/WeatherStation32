#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6radUUFbx"
#define BLYNK_TEMPLATE_NAME "WeatherStation32"

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

#define DHTPIN 5