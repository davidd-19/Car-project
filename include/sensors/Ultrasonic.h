#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pico/stdlib.h"

class Ultrasonic {
private:
    uint trigPin;
    uint echoPin;
    void setupUltrasonicPins();

    int64_t getPulse(); // Uses internal pins

public:
    Ultrasonic(uint triggerPin, uint echoingPin);
    int64_t getDistanceCm(); // Uses internal pins
};

#endif
