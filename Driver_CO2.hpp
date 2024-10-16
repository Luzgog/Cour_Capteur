#include "mbed.h"
#include "PinNames.h"
using namespace std::chrono;

class Driver_CO2
{
private:
    I2C i2c;
    const uint8_t i2c_addr_co2 = 0x62 << 1;
    int send_c02_command(uint16_t address);
    int read_c02_command(uint16_t address, uint8_t *value, uint8_t lenght_byte_of_data, milliseconds delay);
    int write_co2_command(uint16_t address, uint8_t *value);

    uint8_t generate_crc(const uint8_t *data, uint16_t count);

public:
    Driver_CO2(PinName SDA, PinName SCL);
    ~Driver_CO2();
};