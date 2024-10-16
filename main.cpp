/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalIn mypin(PH_1);
DigitalOut myled(LED1);

InterruptIn mypin_irq(PH_1);

bool button_rise_btn = false;
bool button_fall_btn = false;

Timer t;
using namespace std::chrono;

void button_rise() {
    myled =! myled;
    button_rise_btn= true; 
    t.start();
}

void button_fall() {
    myled =! myled;
    button_fall_btn = true; 
    t.stop();
}

int main() {
    if (mypin.is_connected()) {
        printf("mypin is connected and initialized! \n\r");
    }

    mypin.mode(PullNone);

    mypin_irq.rise(&button_rise);
    mypin_irq.fall(&button_fall);

    while (1) {

        if (button_rise_btn == true) {
            printf("mypin has value : 1\n\r");
            button_rise_btn = false; 
        }

        if (button_fall_btn == true) {
            printf("mypin has value : 0\n\r");
            printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            button_fall_btn = false; 
            t == 0;
        }

        wait_us(100000);
    }
}


