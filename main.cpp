/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


BufferedSerial serial (USBTX, USBRX);

#define WAIT 500

int main()
{
    char buf[] = "hello\n\r";   
    serial.set_baud(9600);
    while (true) {
        serial.write(buf, sizeof(buf));
        ThisThread::sleep_for(WAIT);
    }
}
