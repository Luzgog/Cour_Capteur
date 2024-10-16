/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

InterruptIn button(PH_1);
DigitalOut led(LED1);


void flip()
{
    led = !led;
}

int main()
{
    
    button.rise(&flip);  
}