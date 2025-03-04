#include <Arduino.h>
#include <HCSR04.h>
#include "sensor.h"

#define TRIG_PIN 14
#define ECHO_PIN 12

UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);  // Initialize sensor with defined pins

uint32_t sensorReadTimer = 0; // Define the variable

void sensorSetup() {
    // No setup needed for the sensor itself
    sensorReadTimer = millis();
}

float readDistance() {
    sensorReadTimer = millis();
    float distance = distanceSensor.measureDistanceCm();
    if (distance <= 0) {
        distance = 1; // Handle out of range values
    }
    return distance;
}