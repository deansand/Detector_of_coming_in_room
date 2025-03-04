#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

extern uint32_t sensorReadTimer;

void sensorSetup();
float readDistance();

#endif // SENSOR_H