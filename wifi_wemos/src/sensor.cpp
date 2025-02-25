#include <Arduino.h>
#include <HCSR04.h>
#define sensorTrigPin 14
#define sensorEchoPin 12

long duration;
int distance;

void sensorSetup()
{
    Serial.begin(15200);
    pinMode(sensorTrigPin, OUTPUT);
    pinMode(sensorEchoPin, INPUT);
}

void readDistance()
{
    // Clear the trigPin
    digitalWrite(sensorTrigPin, LOW);
    delayMicroseconds(2);

    // Set the trigPin on HIGH state for 10 micro seconds
    digitalWrite(sensorTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(sensorTrigPin, LOW);

    // Read the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(sensorEchoPin, HIGH);

    // Calculate the distance
    distance = duration * 0.034 / 2;

    // Print the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

    delay(1000);
}