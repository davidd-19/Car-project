#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "sensors/Ultrasonic.h"
#include <stdint.h>

// initialize the ultrasonic
Ultrasonic::Ultrasonic(uint triggerPin, uint echoingPin)
    : trigPin(triggerPin), echoPin(echoingPin) {
    setupUltrasonicPins();
}

// sets the pinout for the namespace
void Ultrasonic::setupUltrasonicPins() {
    gpio_init(trigPin);
    gpio_set_dir(trigPin, GPIO_OUT);
    gpio_put(trigPin, 0); // Ensure it's low initially

    gpio_init(echoPin);
    gpio_set_dir(echoPin, GPIO_IN);
}

// send and recives the pulse, theres an included timeout so in the event the pulse
// isnt detected or isnt reflected the code can progress without getting stuck
int64_t Ultrasonic::getPulse() {
    gpio_put(trigPin, 1);
    sleep_us(10);  // Standard 10µs pulse
    gpio_put(trigPin, 0);

    absolute_time_t timeout = make_timeout_time_ms(30);  // 30 ms max wait
    // Wait for echo to go high
    while (gpio_get(echoPin) == 0) {
        if (absolute_time_diff_us(get_absolute_time(), timeout) < 0) return -1;
    }
    absolute_time_t start = get_absolute_time();

    // Wait for echo to go low
    while (gpio_get(echoPin) == 1) {
        if (absolute_time_diff_us(get_absolute_time(), timeout) < 0) return -1;
    }
    absolute_time_t end = get_absolute_time();

    return absolute_time_diff_us(start, end);  // pulse duration in microseconds
}


// converts the pulse into a readable number, the output when
// timeout is -1 as the distance under normal curcumstances can never be negative
int64_t Ultrasonic::getDistanceCm() {
    int64_t pulseLength = getPulse();
    if (pulseLength == -1) return -1;
    return pulseLength / 29 / 2; // Convert to cm
}
