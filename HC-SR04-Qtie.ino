/**************************************************************
 * Property of MoraSquad-Qtie
 **************************************************************
 #define TRIGGER 4
#define ECHO    5

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>//for DTH
#include <DHT.h>//for DTH
#include <SPI.h>//for DTH

// Go to the Project Settings (nut icon).
char auth[] = "02f74a9b887d4096871ebc1d525ba3e6";
char ssid[] = "hansa";
char pass[] = "123Hansa456";
///////////////////////////////////////DHT Libs
#define DHTPIN 2          // What digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer1;
//////////////////////////////////////////////////////////////////////////tweeter Start
void tweetUptime()
{
  long uptime = millis() / 60000L;
  Serial.println("Tweeting every 10 minutes ;)");

  // Actually send the message.
  // Note:
  //   We allow 1 tweet per 15 seconds for now.
  //   Twitter doesn't allow identical subsequent messages.
  Blynk.tweet(String("Running for ") + uptime + " minutes.");
}

void tweetOnButtonPress()
{
  // Invert state, since button is "Active LOW"
  int isButtonPressed = !digitalRead(2);
  if (isButtonPressed) {
    Serial.println("Button is pressed.");

    Blynk.tweet("Yaaay... button is pressed! :)\n #arduino #IoT #blynk @blynk_app");
  }
}*/
//////////////////////////////////////////////////////////////////////////tweeter
//////////////////////////////////////////////////////////////////////////DHT Start
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
//////////////////////////////////////////////////////////////////////////DHT
void setup() {
  Serial.begin (9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  //for DHT
  dht.begin();
  // Setup a function to be called every second
  timer1.setInterval(1000L, sendSensor);

  //for tweet
  //Blynk.tweet("My Arduino project is tweeting using @blynk_app and it’s awesome!\n #arduino #IoT #blynk");
  // Setup a function to be called every 10 minutes
  //timer.setInterval(10L * 60000L, tweetUptime);
  // Setup twitter button on pin 2
  //pinMode(2, INPUT_PULLUP);
  // Attach pin 2 interrupt to our handler
  //attachInterrupt(digitalPinToInterrupt(2), tweetOnButtonPress, CHANGE);
  //
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

  /*if (distance > 100) {
      Blynk.virtualWrite(V0, 255);
  }*/
  if (distance <= 100) {
      Blynk.virtualWrite(V0, 255);
  }
  else {
    Blynk.virtualWrite(V0, 0);
  }

  if (distance <= 75) {
    Blynk.virtualWrite(V1, 255);
  }
  else {
    Blynk.virtualWrite(V1, 0);
  }

  if (distance <= 40) {
    Blynk.virtualWrite(V2, 255);
  }
  else {
    Blynk.virtualWrite(V2, 0);
  }

  if (distance <= 20) {
    Blynk.virtualWrite(V3, 255);
  }
  else {
    Blynk.virtualWrite(V3, 0);
  }

  if (distance <= 10) {
    Blynk.virtualWrite(V4, 255);
  }
  else {
    Blynk.virtualWrite(V4, 0);
  }
  
  //Serial.print(distance);
  //Serial.println("Centimeter:");
  Blynk.virtualWrite(V5, distance);
  delay(200);
  Blynk.run();//Initiates Blynk
  //timer.run();//for tweet
  timer1.run();//for DHT Initiates SimpleTimer
}
