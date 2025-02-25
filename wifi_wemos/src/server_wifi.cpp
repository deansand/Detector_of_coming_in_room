#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#define sensorTrigPin 14
#define sensorEchoPin 12

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

long duration;
int distance;

String readDist() {
  return String(distance);
}

void setup(){
  pinMode(sensorTrigPin, OUTPUT);
  pinMode(sensorEchoPin, INPUT);
  Serial.begin(115200);
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

  // Clear the trigPin
  digitalWrite(sensorTrigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(sensorEchoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(1000);
}