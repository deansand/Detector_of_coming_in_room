#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "setup.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

HCSR04 bme;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDist() {
  return String(bme.readDistance());
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/ditance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDistance().c_str());
  });
  
  // Start server
  server.begin();
}
 
void loop(){
  
}