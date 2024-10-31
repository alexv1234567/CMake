// IMU6050Visualizer.h
#ifndef IMU6050_VISUALIZER_H
#define IMU6050_VISUALIZER_H

#include "IMU6050.h"
#include <GL/glut.h>
#include <cmath>
#include <thread>
#include <chrono>

class IMU6050Visualizer {
public:
    IMU6050Visualizer(IMU6050& imu) : imu(imu) {}

    void startVisualization(int argc, char** argv) {
        // Initialize GLUT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
        glutCreateWindow("IMU6050 Plane Visualization");

        // Set up rendering context
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Set up callbacks
        glutDisplayFunc(displayCallback);
        glutIdleFunc(idleCallback);

        // Set static instance for access in callbacks
        instance = this;

        // Start the main loop
        glutMainLoop();
    }

private:
    IMU6050& imu;
    static IMU6050Visualizer* instance;
    float roll = 0.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;

    static void displayCallback() {
        if (instance) {
            instance->display();
        }
    }

    static void idleCallback() {
        if (instance) {
            instance->updateIMUData();
            glutPostRedisplay();
        }
    }

    void updateIMUData() {
        if (imu.readSensorData()) {
            // Assuming IMU provides roll, pitch, and yaw in radians
            roll = atan2(imu.getAccelY(), imu.getAccelZ());
            pitch = atan2(-imu.getAccelX(), sqrt(imu.getAccelY() * imu.getAccelY() + imu.getAccelZ() * imu.getAccelZ()));
            yaw = imu.getGyroZ() * 0.01f; // Yaw estimate (using gyro data)
        }
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Move back to view the plane
        glTranslatef(0.0f, 0.0f, -5.0f);

        // Apply rotations for roll, pitch, and yaw
        glRotatef(roll * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(pitch * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
        glRotatef(yaw * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);

        // Draw a simple plane
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.7f, 1.0f);
        glVertex3f(-1.0f, -0.1f, 0.0f);
        glVertex3f(1.0f, -0.1f, 0.0f);
        glVertex3f(1.0f, 0.1f, 0.0f);
        glVertex3f(-1.0f, 0.1f, 0.0f);
        glEnd();

        // Swap buffers to display the frame
        glutSwapBuffers();
    }
};

IMU6050Visualizer* IMU6050Visualizer::instance = nullptr;

#endif // IMU6050_VISUALIZER_H
