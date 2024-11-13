#include "Driver_CO2.hpp"
#include "mbed.h"
#include "PinNames.h"
using namespace std::chrono;

Driver_CO2::Driver_CO2(I2C & i2c_ref ) :i2c(i2c_ref)
{
    factory_reset();
}

Driver_CO2::~Driver_CO2()
{
}


int Driver_CO2::send_c02_command(uint16_t address)
{
    static uint8_t buf[2];
    buf[0] = address >> 8;
    buf[1] = address & 0xFF;
    return i2c.write(i2c_addr_co2, (char*)buf, sizeof(buf));
}

int Driver_CO2::read_c02_command(uint16_t address, uint8_t *value, uint8_t lenght_byte_of_data, milliseconds delay)
{
    int res;
    static uint8_t buf[2];
    buf[0] = address >> 8;
    buf[1] = address & 0xFF;
    res = i2c.write(i2c_addr_co2, (char*)buf, sizeof(buf));//we send the command address
    if (res != 0)
    {
        return res;
    }
    ThisThread::sleep_for(delay);//sleep for a minimum time defined in the datasheet

    return i2c.read(i2c_addr_co2, (char*)value, lenght_byte_of_data);//we read the 2 bytes + CRC
}

int Driver_CO2::write_co2_command(uint16_t address, uint8_t *value)
{
    static uint8_t buf[5];
    buf[0] = address >> 8;
    buf[1] = address & 0xFF;
    buf[2] = value[0];
    buf[3] = value[1];

    buf[4] = generate_crc(buf, 5);

    return i2c.write(i2c_addr_co2, (char*)buf, sizeof(buf));
}

#define CRC8_POLYNOMIAL 0x31
#define CRC8_INIT 0xff
uint8_t Driver_CO2::generate_crc(const uint8_t *data, uint16_t count)
{
    uint16_t current_byte;
    uint8_t crc = CRC8_INIT;
    uint8_t crc_bit;
    /* calculates 8-Bit checksum with given polynomial */
    for (current_byte = 0; current_byte < count; ++current_byte)
    {
        crc ^= (data[current_byte]);
        for (crc_bit = 8; crc_bit > 0; --crc_bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ CRC8_POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }
    return crc;
}

int Driver_CO2::read_co2_measurement(uint16_t * co2_ppm, uint16_t * temperature, uint16_t * RH)
{
    uint8_t measure[9];
    uint8_t crc;
    
    read_c02_command(0xec05, measure, 9, milliseconds(2)); //read_measurments

    for (uint8_t i =0; i< 9; i+=3)
    {
        crc = generate_crc(&measure[i], 2);// generate the crc of the data
        if (crc != measure[i +2])//check that it corresponds to the CRC sent by the sensor
        {
            printf("CRC_Error \r\n");
            return 1;
        }
    }
    *co2_ppm = (measure[0] << 8 ) | measure[1];
    *temperature = (measure[3] << 8 ) | measure[4];
    *RH = (measure[6] << 8 ) | measure[7];
    return 0;

}

int Driver_CO2::start_periodic_measurement()
{
    return send_c02_command(0x21b1);//start measurments
}


int Driver_CO2::factory_reset()
{
    return send_c02_command(0x3632);
}

int Driver_CO2::stop_periodic_measurement()
{
    return send_c02_command(0x3f86);
}