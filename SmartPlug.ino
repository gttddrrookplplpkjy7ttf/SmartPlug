
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPLJtgsWHjZ"
#define D0 16
#define LED D0

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

DHT dht;
BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YLWRRj9cIAwfY88pT7Ghn8ykQpF3e__H";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

BLYNK_WRITE(V4)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  if(value == 1)
{
digitalWrite(16,LOW);
}
else
{
digitalWrite(16,HIGH);
}

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

int Temperature;
int Humidity;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(16, OUTPUT);

  dht.setup(D1); // data pin D1

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  timer.run();

  Temperature = dht.getTemperature();
  Humidity = dht.getHumidity();

  // Print serial messages
  Serial.print("Humidity: " + String(Humidity) + " %");
  Serial.print("\t");
  Serial.println("Temperature: " + String(Temperature) + " C");

  // Update Blynk data
  Blynk.virtualWrite(V5, Temperature);
  Blynk.virtualWrite(V6, Humidity);
  
  delay(1000);  
}
