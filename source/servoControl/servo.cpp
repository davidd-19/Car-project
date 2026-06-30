#include "servoControl/servo.h" 
#include "hardware/pwm.h"
#include "pico/stdlib.h"

static uint servo_pin; // shared by all functions in servo but cannot be accessed from outside
static uint slice_num;

void initServo(int gpioPin){
    servo_pin = gpioPin;
    gpio_set_function(servo_pin, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(servo_pin);

    pwm_set_wrap(slice_num, 20000); // 20ms period
    pwm_set_clkdiv(slice_num, 64.0f); //adjsut to get 50hz
    pwm_set_enabled(slice_num, true);
}

void setServoAngle(int angle){
    if (angle < 1 || angle > 360) {
        return;
    }

    int pulse_width_us = 500 + (angle * 2000) / 180;
    int level = pulse_width_us;
    pwm_set_chan_level(slice_num, PWM_CHAN_A, level);
}

