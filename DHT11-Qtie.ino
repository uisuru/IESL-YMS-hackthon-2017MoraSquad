/**************************************************************
 * Property of MoraSquad-Qtie
 **************************************************************
 * This example shows how value can be pushed from Arduino to
 * App project setup:
 *   Value Display widget attached to V5
 *   Value Display widget attached to V6
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = "02f74a9b887d4096871ebc1d525ba3e6";
bool newValue= false;
int ledPin = 16;    // LED connected to digital pin 16
char ssid[] = "IsuruLap";//IsuruLap
char pass[] = "isuruABCD";//isuruABCD

#define DHTPIN 2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V7, h);
  Blynk.virtualWrite(V6, t);
}
BLYNK_CONNECTED() {
    Blynk.syncAll();
}
void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  BLYNK_CONNECTED();
  timer.run(); // Initiates SimpleTimer
  }
