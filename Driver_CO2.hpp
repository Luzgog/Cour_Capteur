#include "mbed.h"
#include "PinNames.h"
using namespace std::chrono;

class Driver_CO2
{
private:
    I2C & i2c;
    const uint8_t i2c_addr_co2 = 0x62 << 1;

    /**
         * @brief send a command to the sensor
         * @param address the address of the command
         * @return int 0 if succes, nonzero on failure  
         */
    int send_c02_command(uint16_t address);

    /**
     * @brief Send a read command to the sensor
     * 
     * @param address the address of the command
     * @param value the returned value
     * @param lenght_byte_of_data the lenght of data we will read (not counting the CRC)
     * @param delay the minimum delay to wait after sending the command to retrieve the data (specified in the datasheet)
     * @return int 0 if succes, nonzero on failure  
     */
    int read_c02_command(uint16_t address, uint8_t *value, uint8_t lenght_byte_of_data, milliseconds delay);

    /**
     * @brief send a write command to the sensor
     * 
     * @param address the address of the command
     * @param value the data you want to write
     * @return 0 if succes, nonzero on failure   
     */
    int write_co2_command(uint16_t address, uint8_t *value);

    /**
         * @brief generate the crc of the data
         * 
         * @param data a pointer to the data
         * @param count the length of the data
         * @return uint8_t the crc
         */
    uint8_t generate_crc(const uint8_t *data, uint16_t count);

public:
    /**
     * @brief Construct a new Driver_CO2 object
     * 
     * @param i2c_ref a reference to the I2C
     */
    Driver_CO2(I2C & i2c_ref);
    ~Driver_CO2();
    
    /**
     * @brief start the periodic measurement. The interval is 5 seconds
     * 
     * @return int 0 if succes, nonzero on failure  
     */
    int start_periodic_measurement();
    /**
         * @brief read the measurements of the sensor
         * 
         * @param co2_ppm the co2 level in ppm
         * @param temperature the temperature as integer. To get the temperature in °C use the following formula : -45 + temperature *175.0 / 65535.0 
         * @param RH the RH as integer. To get the humidity in % use the following formula : RH * 100.0 / 65535.0 
         * @return int 0 if succes, nonzero on failure 
         */
    int read_co2_measurement(uint16_t * co2_ppm, uint16_t * temperature, uint16_t * RH);

    /**
     * @brief stop the measurement of the sensor
     * 
     * @return int 0 if succes, nonzero on failure  
     */
    int stop_periodic_measurement();
    
    /**
     * @brief create a factory reset
     * 
     * @return int 0 if succes, nonzero on failure  
     */
    int Driver_CO2::factory_reset();
};