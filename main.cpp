/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */


#include "mbed.h"
#include <stdio.h>
#include "PinNames.h"
#define VALUE_REP 10

DigitalOut myled(LED1);

Thread thread_1(osPriorityNormal, 1024); 
Thread thread_2(osPriorityNormal, 1024);  


void ping(){
    for(int idx = 0; idx < VALUE_REP; idx++ ){
        printf("Ping\r\n");
        ThisThread::sleep_for(1000);
    }
}

void pong(){
    for(int idx = 0; idx < VALUE_REP; idx++ ){
        printf("Pong\r\n");
        ThisThread::sleep_for(1000);
    }
}

int main(){

    thread_1.start(ping);    
    thread_2.start(pong);

    while(1)
    {
    
    myled =! myled;
    ThisThread::sleep_for(500ms);

    }

}