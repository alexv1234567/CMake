// IMU6050.h
#ifndef IMU6050_H
#define IMU6050_H

#include <cstdint>
#include <cstddef>  // Added to define size_t

class IMU6050 {
public:
    IMU6050(int i2c_address);
    bool initialize();
    bool readSensorData();
    float getAccelX() const;
    float getAccelY() const;
    float getAccelZ() const;
    float getGyroX() const;
    float getGyroY() const;
    float getGyroZ() const;

private:
    int i2c_address;
    int i2c_fd;
    float accel_x, accel_y, accel_z;
    float gyro_x, gyro_y, gyro_z;
    bool writeRegister(uint8_t reg, uint8_t data);
    bool readRegisters(uint8_t reg, uint8_t* buffer, size_t length);
};

#endif // IMU6050_H
