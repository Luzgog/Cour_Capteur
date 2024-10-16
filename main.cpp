/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <stdio.h>
#include "PinNames.h"

using namespace std::chrono;
BufferedSerial serial (USBTX, USBRX);

#define BLINKING_RATE 1s

DigitalOut led(LED1);
// DigitalIn btn(BUTTON1);
InterruptIn btn(BUTTON1);
Timer t;
Ticker ticker_led;


char buf0[] = "BTN 0\n\r";
char buf1[] = "BTN 1\n\r";

bool rise =0;
bool fall = 0;

void callback_rising_edge()
{
    t.start();
    rise =1;
    
}

void callback_falling_edge()
{
    t.stop();
    fall = 1;
}

void callback_ticker()
{
    led = !led;
}

int main()
{
    uint8_t index = 1;
    milliseconds valeur_attente[] = {milliseconds(200),milliseconds(500), seconds(1), seconds(2)};

    char buf_timer[200];
    serial.set_baud(9600);//set the baudrate
    
    btn.mode(PullNone);// no pull up on the BTN
    btn.rise(&callback_rising_edge);//rising edge callback
    btn.fall(&callback_falling_edge);//falling edge callback

    btn.enable_irq();

    ticker_led.attach(&callback_ticker, valeur_attente[0]);//set a ticker for blinking LED

    while (true) {
        if (rise ==1)
        {
            rise = 0;
            serial.write(buf1, sizeof(buf1));
        }
        if (fall == 1)
        {
            fall = 0;
            serial.write(buf0, sizeof(buf0));
            snprintf(buf_timer, sizeof(buf_timer), "The time taken was %llu milliseconds\n\r", duration_cast<milliseconds>(t.elapsed_time()).count());
            t.reset();
            serial.write(buf_timer, strlen(buf_timer));
            
            ticker_led.detach();//removing the callback

            ticker_led.attach(&callback_ticker, valeur_attente[index]);//set a ticker for blinking LED with the new value
            index = (index +1) % (sizeof(valeur_attente)/sizeof(valeur_attente[0]));
        }
    
    }
}
