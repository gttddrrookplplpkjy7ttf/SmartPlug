#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID   "TMPLJtgsWHjZ"
#define D0 16
#define LED D0
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "YLWRRj9cIAwfY88pT7Ghn8ykQpF3e__H";
char ssid[] = "Marisa";
char pass[] = "anandaii";
BLYNK_WRITE(V4) {
  int value = param.asInt();
  if(value == 1)
digitalWrite(16,LOW);
else
digitalWrite(16,HIGH);
  Blynk.virtualWrite(V1, value);
}
BLYNK_CONNECTED() {
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}
void myTimerEvent() {
  Blynk.virtualWrite(V2, millis() / 1000);
}
void setup() {
  Serial.begin(9600);
  pinMode(16, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}
void loop() {
  Blynk.run();
  timer.run();
}

