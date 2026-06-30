#include "functions.h"

#include <cmath>        
#include <cstdio>      
#include "pico/stdlib.h" 
// #include "motor/MotorDriver.h"
// #include "sensors/Ultrasonic.h"

extern "C"
{
#include "motor/MotorDriver.h"
#include "sensors/Ultrasonic.h"
}

//The purpose of the lib is to consolodate all the various functions weve made
//over the coures of the project, and make them easier to use.


//this function ensures the vectors passed are only 10 wide by rotating values
void functions::addToBufferL(int value) {
    if (leftDistances.size() >= BUFFER_SIZE) {
        leftDistances.erase(leftDistances.begin()); 
    }
    leftDistances.push_back(value); 
}

void functions::addToBufferR(int value) {
    if (rightDistances.size() >= BUFFER_SIZE) {
        rightDistances.erase(rightDistances.begin()); 
    }
    rightDistances.push_back(value); 
}

//this function clears the vectors left and right
void functions::clearBuffers() {
    leftDistances.clear();
    rightDistances.clear();
}

//this function calcualtes the average delta in distance
//this should be a smoorther value than the raw distance
float functions::computeAverageDelta(const std::vector<int>& buffer) {
    if (buffer.size() < 8) return 0.0f;

    float sum = 0;
    int skipped = 0;
    for (size_t i = 1; i < buffer.size(); ++i) {
        if ((buffer[i] - buffer[i - 1]) > 5){
            skipped++;
            continue;
        }
        sum += (buffer[i] - buffer[i - 1]);
        printf("\n raw %d", buffer[i]);
    }
    printf("\n SUM %f \n", sum);
    return sum / (buffer.size() - 1 - skipped);
}


//this function checks the angle of the robot by polling L&R, storing it
//then passing into the computeAverageDelta function
float functions::angleCheck(){

    float avgDeltaL = computeAverageDelta(leftDistances);
    float avgDeltaR = computeAverageDelta(rightDistances);

    float angleL = atan2(avgDeltaL, d) * (180.0f / 3.1415926f);
    float angleR = atan2(avgDeltaR, d) * (180.0f / 3.1415926f);

    clearBuffers();

    float avgAngle = (angleL - angleR) / 2.0f;

    return avgAngle;
}

//this function is a wrapper for the angleCheck function and rotate
//this should be called in the main loop, and should correct the robot
void functions::correction() {
    float angle = angleCheck();
    if (fabs(angle) > THRESHOLD) return;
    if (fabs(angle) < THRESHOLD - 25) return;

    if (angle > 0) {
        rotate(static_cast<int>(fabs(angle)), C);
    } else {
        rotate(static_cast<int>(fabs(angle)), CC);
    }
}


