#include "IMU6050.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // Create the IMU6050 object with address 0x69
    IMU6050 imu(0x69);

    // Initialize the IMU
    if (!imu.initialize()) {
        std::cerr << "IMU initialization failed!" << std::endl;
        return -1;
    }

    // Loop to continuously read and display data
    while (true) {
        if (imu.readSensorData()) {
            std::cout << "Accel X: " << imu.getAccelX()
                      << ", Accel Y: " << imu.getAccelY()
                      << ", Accel Z: " << imu.getAccelZ() << std::endl;
            std::cout << "Gyro X: " << imu.getGyroX()
                      << ", Gyro Y: " << imu.getGyroY()
                      << ", Gyro Z: " << imu.getGyroZ() << std::endl;

            // Print a separator line for readability
            std::cout << "---------------------------" << std::endl;
        } else {
            std::cerr << "Failed to read sensor data." << std::endl;
        }

        // Delay for a short period to avoid spamming the sensor too frequently
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}