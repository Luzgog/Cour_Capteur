/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalIn mypin(PH_1);
DigitalOut myled(LED1);

InterruptIn mypin_irq(PH_1);
Ticker ticker;

bool button_rise_btn = false;
bool button_fall_btn = false;

int freq_led = 16; 

Timer t;
using namespace std::chrono;

void button_rise() {
    button_rise_btn = true;
    freq_led = freq_led * 1.5; 
    t.start();
}

void button_fall() {
    button_fall_btn = true;
    t.stop();
    ticker.detach(); 
}

void blink_led() {
    myled = !myled; 
}

void update_ticker() {
    ticker.detach(); 
    ticker.attach(&blink_led, 1.0 / freq_led); 
}

int main() {
    if (mypin.is_connected()) {
        printf("mypin is connected and initialized! \n\r");
    }

    mypin.mode(PullNone);

    mypin_irq.rise(&button_rise);
    mypin_irq.fall(&button_fall);

    while (1) {

        ticker.attach(&blink_led, 1.0 / freq_led); 

        if (button_rise_btn) {
            button_rise_btn = false; 
            update_ticker(); 
            printf("Frequency value: %d Hz\n\r", freq_led);
        }

        if (button_fall_btn) {
            printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            button_fall_btn = false; 
            t.reset(); 
        }
        wait_us(100000); 
    }
}
