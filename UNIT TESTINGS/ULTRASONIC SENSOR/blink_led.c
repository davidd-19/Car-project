#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

uint trigPin1 = 16;
uint echoPin1 = 17;

uint trigPin2 = 18;
uint echoPin2 = 19;

void core1_entry() {

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    while (true) {
        int delay = multicore_fifo_pop_blocking();
        if (delay > 100) {
            delay = 100;
        }
        gpio_put(25, 1);
        sleep_ms(delay);
        gpio_put(25, 0);
    }
}

int main(){

    stdio_init_all(); 
    setupUltrasonicPins(trigPin1, echoPin1);
    setupUltrasonicPins(trigPin2, echoPin2);

    multicore_launch_core1(core1_entry);


    while (true) { 
        int distance1 = getCm(trigPin1, echoPin1);
        int distance2 = getCm(trigPin2, echoPin2);

        int delay = (distance1 + distance2);

        multicore_fifo_push_blocking(delay);

        printf("\n %d cm, %d cm, %d delay", distance1, distance2, delay); 

        sleep_ms(100);
    }
}

