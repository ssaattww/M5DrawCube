/**
 * @file main.cpp
 * @author ssaattwwoeg
 * @brief 
 * draw cube with mpu6886
 * @version 0.1
 * @date 2022-10-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define M5STACK_MPU6886 

#include <M5Core2.h>
#define LGFX_AUTODETECT
#define LGFX_USE_V1

#include <LovyanGFX.hpp>

#include "cube.hpp"

static LGFX lcd;
static LGFX_Sprite canvas(&lcd);

void setup() {
    M5.begin();
    M5.IMU.Init();

    lcd.init();
    // canvas.createSprite(lcd.width(), lcd.height());
    Serial.begin(115200);

}

void loop() {

    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;
    float pitch, roll, yaw;
    float my_pitch, my_roll, my_yaw;

    M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
    M5.IMU.getAccelData(&accX,&accY,&accZ);
    M5.IMU.getAhrsData(&pitch,&roll,&yaw);
    // cube(roll, pitch, yaw);
    cube(roll, pitch, yaw, accX ,accY ,accZ , lcd);

    my_roll = atan(accY / accZ) * RAD_TO_DEG;
    my_pitch = atan(-accX / sqrtf(accY*accY + accZ*accZ)) * RAD_TO_DEG;

    lcd.setCursor(0,0);
    lcd.printf("gyro=(%5.3f, %5.3f, %5.3f)\n", gyroX, gyroY, gyroZ);
    lcd.printf("acc=(%5.3f, %5.3f, %5.3f)\n", accX, accY, accZ);
    lcd.printf("PRY=(%5.3f, %5.3f, %5.3f)\n", pitch, roll, yaw);
    // lcd.printf("pitch = %5.1f, roll = %5.1f", my_pitch, my_roll);
    
    delay( 5 );
}