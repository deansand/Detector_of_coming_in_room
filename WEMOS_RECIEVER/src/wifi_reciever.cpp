#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "led_strip.h"
#include "wifi_reciever.h"

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

//TODO: fix software WDT reset, hardware reset
const char* serverNameDistance = "http://192.168.4.1/distance";
const char* serverNameLed = "http://192.168.4.1/led";

String ledData;
String distance;

uint32_t previousTime = 0;
const uint32_t timeout = 2000;

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  Serial.println("Starting HTTP request...");
  http.begin(client, serverName);

  int httpResponseCode = http.GET();
  String payload = "--";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  Serial.println("HTTP request completed.");
  return payload;
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  setupLedStrip();
}

void loop() {
  unsigned long currentTime = millis();
  if(currentTime - previousTime >= timeout) {
    if(WiFi.status() == WL_CONNECTED) {
      Serial.println("Starting distance and LED data requests...");
      // Synchronously get distance and LED data
      distance = httpGETRequest(serverNameDistance);
      ledData = httpGETRequest(serverNameLed);

      Serial.println("Distance:" + distance);
      Serial.println("LED Data:" + ledData);

      previousTime = currentTime;
    } else {
      Serial.println("WiFi Disconnected");
    }
  }
  loopUseLED(&ledColor);
}