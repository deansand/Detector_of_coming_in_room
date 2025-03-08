#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "sensor.h"

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDist() {
  return String(readDistance());
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Initialize the sensor
  sensorSetup();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // not found handler
  // rroot handler
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/", "Hello, world");
  });

  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/distance", readDist());
  });
  
  // Start server
  server.begin();
}
 
void loop()
{
  static uint32_t now = millis();

  if (now - sensorReadTimer >= 5000) {
    Serial.println(readDistance());
  }
}