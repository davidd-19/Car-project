#ifndef SERVO_H
#define SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

void initServo(int gpioPin);
void setServoAngle(int angle);

#ifdef __cplusplus
}
#endif

#endif // SERVO_H
