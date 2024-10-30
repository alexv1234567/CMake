// IMU6050.cpp
#include "IMU6050.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstddef>  // Define size_t
#ifdef __linux__
#include <linux/i2c-dev.h>
#elif defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>  // Add this for CFTypeRef
// Removed IOKit includes to avoid CFTypeRef issues
#else
#error "This code requires a Linux or macOS system."
#endif

IMU6050::IMU6050(int i2c_address) : i2c_address(i2c_address), i2c_fd(-1), accel_x(0), accel_y(0), accel_z(0), gyro_x(0), gyro_y(0), gyro_z(0) {}

bool IMU6050::initialize() {
#ifdef __linux__
    i2c_fd = open("/dev/i2c-1", O_RDWR);
    if (i2c_fd < 0) {
        std::cerr << "Failed to open I2C bus" << std::endl;
        return false;
    }

    if (ioctl(i2c_fd, I2C_SLAVE, i2c_address) < 0) {
        std::cerr << "Failed to connect to IMU6050" << std::endl;
        close(i2c_fd);
        return false;
    }

    // Wake up the IMU6050
    return writeRegister(0x6B, 0x00);
#elif defined(__APPLE__)
    // macOS-specific initialization (placeholder)
    std::cerr << "I2C initialization for macOS is not implemented." << std::endl;
    return false;
#endif
}

bool IMU6050::readSensorData() {
    uint8_t buffer[14];
    if (!readRegisters(0x3B, buffer, 14)) {
        return false;
    }

    accel_x = static_cast<int16_t>((buffer[0] << 8) | buffer[1]) / 16384.0f;
    accel_y = static_cast<int16_t>((buffer[2] << 8) | buffer[3]) / 16384.0f;
    accel_z = static_cast<int16_t>((buffer[4] << 8) | buffer[5]) / 16384.0f;
    gyro_x = static_cast<int16_t>((buffer[8] << 8) | buffer[9]) / 131.0f;
    gyro_y = static_cast<int16_t>((buffer[10] << 8) | buffer[11]) / 131.0f;
    gyro_z = static_cast<int16_t>((buffer[12] << 8) | buffer[13]) / 131.0f;

    return true;
}

float IMU6050::getAccelX() const {
    return accel_x;
}

float IMU6050::getAccelY() const {
    return accel_y;
}

float IMU6050::getAccelZ() const {
    return accel_z;
}

float IMU6050::getGyroX() const {
    return gyro_x;
}

float IMU6050::getGyroY() const {
    return gyro_y;
}

float IMU6050::getGyroZ() const {
    return gyro_z;
}

bool IMU6050::writeRegister(uint8_t reg, uint8_t data) {
#ifdef __linux__
    uint8_t buffer[2] = {reg, data};
    if (write(i2c_fd, buffer, 2) != 2) {
        std::cerr << "Failed to write to register" << std::endl;
        return false;
    }
    return true;
#elif defined(__APPLE__)
    // macOS-specific write implementation (placeholder)
    std::cerr << "I2C write for macOS is not implemented." << std::endl;
    return false;
#endif
}

bool IMU6050::readRegisters(uint8_t reg, uint8_t* buffer, size_t length) {
#ifdef __linux__
    if (write(i2c_fd, &reg, 1) != 1) {
        std::cerr << "Failed to write register address" << std::endl;
        return false;
    }

    if (read(i2c_fd, buffer, length) != static_cast<ssize_t>(length)) {
        std::cerr << "Failed to read from register" << std::endl;
        return false;
    }
    return true;
#elif defined(__APPLE__)
    // macOS-specific read implementation (placeholder)
    std::cerr << "I2C read for macOS is not implemented." << std::endl;
    return false;
#endif
}
