// main.cpp
#include "IMU6050.h"
#include <iostream>

int main() {
    IMU6050 imu(0x68);
    if (!imu.initialize()) {
        std::cerr << "Failed to initialize IMU6050" << std::endl;
        return 1;
    }

    if (imu.readSensorData()) {
        std::cout << "Accel X: " << imu.getAccelX() << " g" << std::endl;
        std::cout << "Accel Y: " << imu.getAccelY() << " g" << std::endl;
        std::cout << "Accel Z: " << imu.getAccelZ() << " g" << std::endl;
        std::cout << "Gyro X: " << imu.getGyroX() << " deg/s" << std::endl;
        std::cout << "Gyro Y: " << imu.getGyroY() << " deg/s" << std::endl;
        std::cout << "Gyro Z: " << imu.getGyroZ() << " deg/s" << std::endl;
    } else {
        std::cerr << "Failed to read sensor data" << std::endl;
    }

    return 0;
}

