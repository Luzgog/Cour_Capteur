#include "Driver_CO2.hpp"
#include "mbed.h"
#include "PinNames.h"
using namespace std::chrono;

Driver_CO2::Driver_CO2(PinName SDA, PinName SCL): i2c(SDA,SCL)
{
    printf("test drv\n\r");
    i2c.frequency(100000);
    uint8_t buf[2] = {0xbe, 0xef};
    printf("crc 0xbeef : %x\n\r", generate_crc(buf, 2));

    send_c02_command(0x21b1);//start measurments
    ThisThread::sleep_for(seconds(6));

    uint8_t measures[7];
    int res = read_c02_command(0xec05, measures, 6, milliseconds(2)); //read_measurment

    printf("Res = %d\r\n", res);
    printf("Value = \r\n");
    for (int i =0; i <6; i++)
    {
        printf("0x%x\r\n", measures[i]);
    }


    
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

    res = i2c.write(i2c_addr_co2, (char*)buf, sizeof(buf));
    if (res != 0)
    {
        return res;
    }
    ThisThread::sleep_for(delay);

    for (int i=0; i < lenght_byte_of_data; i+=2)
    {
        res = i2c.read(i2c_addr_co2, (char*)&value[i], 3);
        if (res != 0)
        {
            return res;
        }

    }
    return i2c.read(i2c_addr_co2, (char*)value, 3);
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
