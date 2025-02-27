#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

const char* serverName = "http://192.168.4.1/distance";

String distance;

unsigned long previousTime = 0;
const long timeout = 2000;

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  int httpResponseCode = http.GET();
  String payload = "--";

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
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
}

void loop() {
  unsigned long currentTime = millis();
  if(currentTime - previousTime >= timeout) {
    if(WiFi.status() == WL_CONNECTED) {
      distance = httpGETRequest(serverName);
      Serial.println("Distance:" + distance);
      previousTime = currentTime;
    } else {
      Serial.println("WiFi Disconnected");
    }
  }
}
