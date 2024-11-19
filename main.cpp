/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Driver_CO2.hpp"

int main() {
    I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

    Driver_CO2 co2_sensor(i2c);

    if (co2_sensor.start_periodic_measurement() != 0) {
        printf("Erreur : Impossible de démarrer les mesures périodiques.\r\n");
        return 1;
    }

    uint16_t co2_ppm;
    uint16_t temperature;
    uint16_t humidity;


    while (true) {

        if (co2_sensor.read_co2_measurement(&co2_ppm, &temperature, &humidity) == 0) {
            printf("CO2: %u ppm, Température: %u, Humidité: %u\r\n", co2_ppm, temperature, humidity);
        } else {
            printf("Erreur : Lecture des mesures échouée.\r\n");
        }
        ThisThread::sleep_for(1s);
    }

    return 0;
}