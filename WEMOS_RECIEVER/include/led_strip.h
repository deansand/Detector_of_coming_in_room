#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <Arduino.h>

#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 7

#define RESOLUTION 256

typedef struct {
    uint8_t RED;
    uint8_t GREEN;
    uint8_t BLUE;
} rgb_t;

enum ledColor {
    RED,
    GREEN,
    BLUE
};

extern rgb_t ledColor;

void setupLedStrip();
void setLedColor(uint8_t RED, uint8_t GREEN, uint8_t BLUE);
void loopUseLED();

#endif // LED_STRIP_H