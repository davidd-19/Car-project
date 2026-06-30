#ifndef __ULTRASONIC_H_
#define __ULTRASONIC_H_

void setupUltrasonicPins(int trigPin, int echoPin);

int getCm(int trigPin, int echoPin);


#endif