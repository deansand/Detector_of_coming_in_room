#include <Arduino.h>
#include <HCSR04.h>
#include "sensor.h"

UltraSonicDistanceSensor distanceSensor(14, 12);  // Initialize sensor that uses digital pins 13 and 12.

void sensorSetup() {
    // No setup needed for the sensor itself
}

float readDistance() {
    return distanceSensor.measureDistanceCm();
}