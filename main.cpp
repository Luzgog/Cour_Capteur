/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalIn  mypin(PH_1); 
DigitalOut myled(LED1);

int main()
{
    // check mypin object is initialized and connected to a pin
    if (mypin.is_connected()) {
        printf("mypin is connected and initialized! \n\r");
    }
    mypin.mode(PullNone);

    // press the button and see the console / led change
    while (1) {
        printf("mypin has value : %d \n\r", mypin.read());
        myled = mypin;
    }
}