#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <Arduino.h>

#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 7

#define RESOLUTION 256

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_t;

extern rgb_t ledColor;

void setupLedStrip();
void setLedColor(uint8_t red, uint8_t green, uint8_t blue);
void loopUseLED();

#endif // LED_STRIP_H