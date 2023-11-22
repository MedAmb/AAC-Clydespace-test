#include "i2c_driver.hpp"

std::shared_ptr<MockI2CDriver> MockI2CDriver::mock_i2c_driver_{nullptr};

uint8_t i2c_read(uint8_t bus_address, uint8_t register_address, uint8_t *buffer, uint16_t length) {
    return MockI2CDriver::GetMockI2CDriver()->i2c_read(bus_address, register_address, buffer, length);
}

uint8_t i2c_write(uint8_t bus_address, uint8_t register_address, uint8_t *data, uint16_t length) {
    return MockI2CDriver::GetMockI2CDriver()->i2c_write(bus_address, register_address, data, length);
}