// #include "sensors/MPU6050.h"
// #include "motor/DEV_Config.h"
// #include "pico/time.h"
// #include <cmath>

// #define SCL 21
// #define SDA 20
// #define I2C_PORT i2c0

// #define ADDR 0x68
// #define wake 0x6B
// #define filter 0x1A
// #define samplerate 0x19
// #define gyroconfig 0x1B
// #define accelconfig 0x1C

// #define GYRO_SENS 131.0

// // init the gyro and i2c
// gyro::gyro() {
//     last_time = time_us_64();

//     // init i2c for mpu & motor dirver
//     i2c_init(I2C_PORT, 100*1000);
//     gpio_set_function(SDA,GPIO_FUNC_I2C);
//     gpio_set_function(SCL,GPIO_FUNC_I2C);
//     gpio_pull_up(SDA);
//     gpio_pull_up(SCL);

//     // start the MPU6050
//     DEV_Delay_ms(100);

//     DEV_I2C_WriteByte(ADDR, wake, 0x00); // Wake up the MPU6050
//     DEV_I2C_WriteByte(ADDR, filter, 0x03); // Set the DLPF to 260Hz
//     DEV_I2C_WriteByte(ADDR, samplerate, 0x04); // Set the sample rate to 1kHz
//     DEV_I2C_WriteByte(ADDR, gyroconfig, 0x00); // Set the gyro full scale range to ±250°/s
//     DEV_I2C_WriteByte(ADDR, accelconfig, 0x00); // Set the accelerometer full scale range to ±2g

//     calibrate(); // Calibrate the gyroscope
// }


// // This function reads the gyroscope values from the MPU6050
// void gyro::read_gyro(float *gyro_x, float *gyro_y, float *gyro_z){
//     int16_t z = DEV_I2C_ReadByte(ADDR, 0x47) << 8 | DEV_I2C_ReadByte(ADDR, 0x48);
//     if (gyro_z) *gyro_z = z;
// }


// // This function cleans the gyroscope readings by removing the offset and dividing by the sensitivity
// void gyro::clean_gyro(float *gyro_x, float *gyro_y, float *gyro_z) {
// 	read_gyro(nullptr, nullptr, gyro_z); //Store raw values into variables
// 	*gyro_z = round((*gyro_z - G_OFF_Z) * 1000.0 / GYRO_SENS) / 1000.0;
// }


// // This function calculates the angle based on the gyroscope readings
// void gyro::angle() {
//     delta(); 
//     clean_gyro(nullptr, nullptr, &gyro_z);

//     if (fabs(gyro_z) < 0.1) gyro_z = 0;
//     current_angle_z += gyro_z * dt;

//     if (!is_turning) {
//         float correction_gain = 0.01f;
//         current_angle_z += (reference_angle - current_angle_z) * correction_gain;
//     }
// }

// float gyro::get_angle() const {
//     return current_angle_z;
// }

// void gyro::set_straight_reference(float current_angle) {
//     reference_angle = current_angle;
// }


// // calcs the time difference in seconds
// void gyro::delta() {
//     now = time_us_64();
//     dt = (now - last_time) / 1e6;
//     if (dt > 0.5) dt = 0.0;  // Drop if too large, like after sleep
//     last_time = now;
// }


// // currently only for z
// void gyro::calibrate() {
//     int32_t sum_z = 0;
//     const int iterations = 1000;

//     for (int i = 0; i < iterations; ++i) {
//         uint16_t raw_z = DEV_I2C_ReadByte(ADDR, 0x47) << 8 | DEV_I2C_ReadByte(ADDR, 0x48);
//         sum_z += (int16_t)raw_z;
//         DEV_Delay_ms(2);
//     }
//     G_OFF_Z = sum_z / iterations;
// }