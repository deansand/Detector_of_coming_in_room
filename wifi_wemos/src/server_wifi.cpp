#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <HCSR04.h>

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

UltraSonicDistanceSensor sensor(14, 12);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDist() {
  return String(sensor.measureDistanceCm());
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", readDist());
  });
  
  // Start server
  server.begin();
}
 
void loop(){
  
}