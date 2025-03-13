#include "led_strip.h"
#include "wifi_reciever.h"

const uint8_t priority = 1;

uint32_t previousTime = 0;
const uint32_t timeout = 7000;

extern String distance;
extern String ledData;

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

rgb_t setLedWeb(String data) {
    // ledData = data;
    rgb_t rgb;
    if (data.length() > 0) {
       
        rgb.red = data.substring(0, data.indexOf(',')).toInt();
        rgb.green = data.substring(data.indexOf(',') + 1, data.lastIndexOf(',')).toInt();
        rgb.blue = data.substring(data.lastIndexOf(',') + 1).toInt();

        // color->red = red;
        // color->green = green;
        // color->blue = blue;

    }
    return rgb;
}

void loopUseLED(rgb_t *color) {
    uint32_t currentTime = millis();
    if (priority == 1) 
    {
        if (distance.toInt() < 15 && currentTime - previousTime >= timeout) {
                color->red = UINT8_MAX;
                color->green = 0;
                color->blue = 0;
                previousTime = currentTime;
        } else {
            color->red = 0;
            color->green = 0;
            color->blue = UINT8_MAX;
        }
    } else {
        rgb_t tempColor = setLedWeb(ledData);
        *color = tempColor;
    }
    setLedColor(ledColor);
}

