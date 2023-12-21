#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
char auth[] = "6KrdBuNMuaYf5PyS6v1TOF2CJYyFOQyw"; 
char ssid[] = "Wokwi-GUEST"; 
char pass[] = ""; 
int pinLED = 2; 
const int DHT_PIN1 = 15;
const int DHT_PIN2 = 14;
int relevador1 = 22;
int relevador1 = 23;
int botonstate = HIGH;
DHTesp dhtSensor;
WidgetLED LEDtemp(V8); 
WidgetLED LEDHum(V1); 
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(pinLED, OUTPUT);
  dhtSensor.setup(DHT_PIN1, DHTesp::DHT22);
  pinMode(relevador1, OUTPUT);
  pinMode(botonstate, INPUT_PULLUP);
  digitalWrite(relevador1, LOW);
  pinMode(relevador2, OUTPUT);
  pinMode(botonstate, INPUT_PULLUP);
  digitalWrite(relevador2, LOW);
  }
void loop() {
  Blynk.run();
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  delay(1000);
  Blynk.virtualWrite(V5, data.temperature);
  Blynk.virtualWrite(V6, data.humidity);
  if (data.temperature > 23) {
      digitalWrite(relevador1, HIGH);
      Serial.println("Temperature On");
      LEDtemp.on();
   }
  if(data.temperature <= 23)
LEDtemp.off();
if(data.humidity < 30) {
      digitalWrite(relevador2, HIGH);
      Serial.println("Humidity On");
      LEDHum.on();
  }
  if(data.humidity >= 30)
    LEDHum.off();
}
BLYNK_WRITE(V4)
{
  int ledState = param.asInt();
  if (ledState == 1)
    digitalWrite(pinLED, HIGH);
else
    digitalWrite(pinLED, LOW);
}
