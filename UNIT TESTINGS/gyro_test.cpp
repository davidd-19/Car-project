#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"

extern "C"
{
#include "sensors/MPU6050.h"
}


// Led Output
const uint ledpin = 25;

gyro mpu;


void initLED()
{
    gpio_init(ledpin);
    gpio_set_dir(ledpin, GPIO_OUT);
    gpio_put(ledpin, 0);
    adc_init();
    adc_gpio_init(aout1);
    adc_gpio_init(aout2);
    adc_gpio_init(aout3);
    adc_select_input(2);
}


int main()
{
    stdio_init_all();
    initLED();

    DEV_Module_Init();
    Motor_Init(); 

    float angle_z = 0.0;

    while(true){
        gpio_put(25, 1);
        printf("gyro\n");

        mpu.angle(&angle_z);
        printf("z: %f\n", angle_z);
        sleep_ms(100);
        gpio_put(25, 0);
    }
    return 0;
}
