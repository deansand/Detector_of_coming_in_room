#include "led_strip.h"
#include "wifi_reciever.h"

extern String distance;
rgb_t ledColor;

void setupLedStrip() {
    analogWriteResolution(RESOLUTION);
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
}

void setLedColor(rgb_t color) {
    analogWrite(RED_PIN, color.red);
    analogWrite(GREEN_PIN, color.green);
    analogWrite(BLUE_PIN, color.blue);
}

void loopUseLED() {
    if (distance.toInt() < 15) {
        ledColor.red = 255;
        ledColor.green = 0;
        ledColor.blue = 0;
    } else {
        ledColor.red = 0;
        ledColor.green = 0;
        ledColor.blue = 255;
    }
    setLedColor(ledColor);
}