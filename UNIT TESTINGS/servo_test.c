#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
extern "C"
{
#include "motor/MotorDriver.h"
#include "sensors/Ultrasonic.h"
#include "servoControl/servo.h" 
}

//Ultrasonic Pins
const uint trigPinR = 5;
const uint echoPinR = 4;

const uint trigPinF = 8;
const uint echoPinF = 9;

const uint trigPinL = 7;
const uint echoPinL = 6;

// IR Input
const uint aout3 = 26;
const uint aout2 = 27;
const uint aout1 = 28;

// Led Output
const uint ledpin = 25;

// Rotate threshdold
const int THRESHOLD = 10;


Ultrasonic ultrasonicF(trigPinF, echoPinF);
Ultrasonic ultrasonicL(trigPinL, echoPinL);
Ultrasonic ultrasonicR(trigPinR, echoPinR);



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


//IR test
bool betOnBlack()
{
    uint16_t ir = 0;

    adc_select_input(0);
    ir += adc_read();

    adc_select_input(1);
    ir += adc_read();

    adc_select_input(2);
    ir += adc_read();

    printf("\n %d sensor output", ir);
    if (ir < 9000){
        return true;
    } else {
        return false;
    }

}



//Servo
uint angleCheck(ROT rotate)
{
    int angle = (rotate == 0) ? 360 : 1; // Start at edge
    int modifier = (rotate == 0) ? -2 : 2; // C or CCW
    uint last_distance = 0;
    uint current_distance = 0;
    int start_angle = angle;

    setServoAngle(angle);
    sleep_ms(300);        

    last_distance = ultrasonicF.getDistanceCm();

    while (true) {
        angle += modifier;

        if (angle < 1 || angle > 360) {
            break; // Safety limit
        }

        setServoAngle(angle);
        sleep_ms(100);

        current_distance = ultrasonicF.getDistanceCm();

        // printf("\nDistance: %d (last: %d) at angle: %d\n", current_distance, last_distance, angle);

        if (current_distance == 0) continue; 

        if (current_distance > last_distance && last_distance != 0) {
            break; // Distance started increasing => passed closest point
        }

        last_distance = current_distance;
    }

    setServoAngle(195);
    return (start_angle - angle) - modifier;  // Return the angle just before it started increasing
}




int main()
{
    stdio_init_all();
    initLED();

    DEV_Module_Init();
    Motor_Init(); 
    initServo(10);

    int previous_value[2] = {0, 0};

    int angles[5] = {0,0,0,0,0};

    while (true)
    {
        gpio_put(25, 1);

        // int distanceF = ultrasonicF.getDistanceCm();
        // int distanceL = ultrasonicL.getDistanceCm();
        // int distanceR = ultrasonicR.getDistanceCm();
        // int speed = 80;

        
        // printf("\n F %d cm, L %d cm, R %d cm", distanceF, distanceL, distanceR);
        // printf("\n %d", distanceF);
        
        // int WALL {15};

        for (int i = 0; i < 5; i++){
        angles[i] = angleCheck(C);
        Motor_All(RIGHT, 80);
        sleep_ms(50);
        Motor_Stop_All();
        }

        int sum = 0;
        for (int i = 0; i < 5; i++) {
        sum += angles[i];
        }
        int angle = (sum / 5);

        printf("angle %d", angle);

        rotate (angle, C);

        continue;

        // int error = distanceL - distanceR;
        // int tolerance = 5;
        
        // if (distanceF > WALL)
        // {
        //     if ((distanceL < 20 && distanceR < 20) && (error < -tolerance || error > tolerance) && (previous_value[0] < distanceL || previous_value[1] < distanceR))
        //     {
        //         if(error < -tolerance )
        //         {
        //             printf(" CORRECTING RIGHT");
        //             Motor_All(CORNER_R, speed);
        //         }

        //         else
        //         {
        //             printf(" CORRECTING LEFT");
        //             Motor_All(CORNER_L, speed);
        //         }
        //     }

        //     else
        //     {
        //         printf(" GOING FORWARD");
        //         Motor_All(FORWARD, speed);
        //     }
        // }
        
        // else if ((distanceF <= WALL && distanceL > WALL && distanceR > WALL) || 
        //          (distanceF <= WALL && distanceL <= WALL && distanceR > WALL))
        // {
        //     printf(" TURNING RIGHT");
        //     rotate (90, C);
        // }

        // else if ((distanceF <= WALL && distanceL > WALL && distanceR <= WALL))
        // {
        //     printf(" TURNING LEFT");
        //     rotate (90, CC);
        // }

        // else if (distanceF <= WALL && distanceL <= WALL && distanceR <= WALL)
        // {
        //     printf(" DEAD END - ROTATING");
        //     rotate (180, CC);
        // }


        // previous_value[0] = distanceL;
        // previous_value[1] = distanceR;
        gpio_put(25, 0);
    }

    return 0;
}