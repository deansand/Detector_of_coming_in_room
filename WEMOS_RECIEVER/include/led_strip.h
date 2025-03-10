#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <Arduino.h>

#define RED_PIN D5
#define GREEN_PIN D6
#define BLUE_PIN D7

#define RESOLUTION 255

typedef struct rgb{
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
} rgb_t;

typedef enum ledColor_e {
    NO_COLOR=0,
    RED=1,
    GREEN,
    BLUE
}colorType_t;

extern rgb_t ledColor;

void setupLedStrip();
void setLedColor(uint8_t r, uint8_t gr, uint8_t bl);
void loopUseLED(rgb_t *color);

#endif // LED_STRIP_H