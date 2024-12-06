/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <stdio.h>
#include "PinNames.h"
#include "Driver_CO2.hpp"
#include <math.h>

BufferedSerial serial (USBTX, USBRX);
using namespace std::chrono;


int main()
{
    I2C i2c (P1_I2C_SDA, P1_I2C_SCL);
    i2c.frequency(100000);//set i2c to 100 khz
    uint16_t co2_ppm, temperature,RH;
    serial.set_baud(9600);
    Driver_CO2 drv(i2c);
    ThisThread::sleep_for(seconds(6));
    drv.start_periodic_measurement();
    while(1)
    {
        int res = drv.read_co2_measurement(&co2_ppm, &temperature, &RH);
        printf("Res = %d\r\n", res);
        printf("CO2 : %d ppm\n\r", co2_ppm );
        printf("Temperature : %d °C\r\n", (int)floorf(-45 + temperature *175.0 / 65535.0));
        printf("RH %d % \r\n",(int)floorf( RH * 100.0 / 65535.0));
        ThisThread::sleep_for(seconds(5));//sleep for a minimum time defined in the datasheet

    }

}