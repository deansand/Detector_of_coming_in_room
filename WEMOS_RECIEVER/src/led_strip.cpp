#include "led_strip.h"
#include "wifi_reciever.h"

const uint8_t priority = 1;

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
    analogWrite(RED_PIN, color.RED);
    analogWrite(GREEN_PIN, color.GREEN);
    analogWrite(BLUE_PIN, color.BLUE);
}

void loopUseLED() {
    if (priority == 1) {
        if (distance.toInt() < 15) {
            ledColor.RED = 255;
            ledColor.GREEN = 0;
            ledColor.BLUE = 0;
        } else {
            ledColor.RED = 0;
            ledColor.GREEN = 0;
            ledColor.BLUE = 255;
        }
    } else {
        if (ledData.length() > 0) {
            int red = ledData.substring(0, ledData.indexOf(',')).toInt();
            int green = ledData.substring(ledData.indexOf(',') + 1, ledData.lastIndexOf(',')).toInt();
            int blue = ledData.substring(ledData.lastIndexOf(',') + 1).toInt();

            ledColor.RED = red;
            ledColor.GREEN = green;
            ledColor.BLUE = blue;
        }
    }
    setLedColor(ledColor);
}