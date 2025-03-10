#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "sensor.h"

// Function to set LED color
void setLedColor(uint8_t red, uint8_t green, uint8_t blue) {
  // Add your implementation here
}

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";


IPAddress local_IP(192, 168, 4, 0);
IPAddress gateway(192, 168, 4, 0);
IPAddress subnet(255, 255, 255, 0);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDist() {
  return String(readDistance());
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Configure the access point
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  } else {
    Serial.println("STA Configured");
  }
  
  // Initialize the sensor
  sensorSetup();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter if you want the AP (Access Point) to be open
  if (WiFi.softAP(ssid, password)) {
    Serial.println("AP Started");
  } else {
    Serial.println("AP Failed to start");
  }

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jscolor/2.0.4/jscolor.min.js"></script>
      </head>
      <body>
        <div class="container">
          <div class="row">
            <h1>ESP Color Picker</h1>
          </div>
          <a class="btn btn-primary btn-lg" href="#" id="change_color" role="button">Change Color</a>
          <input class="jscolor {onFineChange:'update(this)'}" id="rgb">
        </div>
        <script>
          function update(picker) {
            document.getElementById('rgb').innerHTML = Math.round(picker.rgb[0]) + ', ' +  Math.round(picker.rgb[1]) + ', ' + Math.round(picker.rgb[2]);
            document.getElementById("change_color").href = "/led?r=" + Math.round(picker.rgb[0]) + "&g=" +  Math.round(picker.rgb[1]) + "&b=" + Math.round(picker.rgb[2]);
          }
        </script>
      </body>
      </html>
    )rawliteral");
  });

  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", readDist());
  });
  
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("r") && request->hasParam("g") && request->hasParam("b")) {
      uint8_t red = request->getParam("r")->value().toInt();
      uint8_t green = request->getParam("g")->value().toInt();
      uint8_t blue = request->getParam("b")->value().toInt();
      setLedColor(red, green, blue);
      request->send(200, "text/plain", "LED color set");
    } else {
      request->send(400, "text/plain", "Missing parameters");
    }
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