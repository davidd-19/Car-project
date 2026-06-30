#ifndef MPU6050_H
#define MPU6050_H

#include "MPU6050.h"
#include "motor/DEV_Config.h"
#include "pico/time.h"


class gyro {
private:
    uint64_t last_time, now;
    float gyro_x = 0, gyro_y = 0, gyro_z = 0, dt;
    int16_t G_OFF_X = 0, G_OFF_Y = 0, G_OFF_Z = 0; 
    
    void read_gyro(float *gyro_x, float *gyro_y, float *gyro_z);
    void clean_gyro(float *gyro_x, float *gyro_y, float *gyro_z);
    void delta();
    

public:
    float angle_x, angle_y, angle_z;
    bool is_turning = false;
    float reference_angle = 0.0f;
    float current_angle_z = 0.0f;

    gyro();
    void calibrate();
    void angle();
    void set_straight_reference(float current_angle);
    float get_angle() const;
};

#endif 