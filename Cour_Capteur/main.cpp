/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <stdio.h>
#include "PinNames.h"
#include "Driver_CO2.hpp"


BufferedSerial serial (USBTX, USBRX);
using namespace std::chrono;


int main()
{
    serial.set_baud(9600);
    printf("test\r\n");
    Driver_CO2 drv(P1_I2C_SDA, P1_I2C_SCL);

    while(1)
    {

    }

}
