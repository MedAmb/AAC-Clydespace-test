#include "gmock/gmock.h"

#include <memory>

uint8_t i2c_read(uint8_t bus_address, uint8_t register_address, uint8_t *buffer,
uint16_t length);

uint8_t i2c_write(uint8_t bus_address, uint8_t register_address, uint8_t *data,
uint16_t length);


class MockI2CDriver {
public:
    MOCK_METHOD4(i2c_read, uint8_t(uint8_t bus_address, uint8_t register_address,
    uint8_t *buffer, uint16_t length));
    MOCK_METHOD4(i2c_write, uint8_t(uint8_t bus_address, uint8_t register_address,
    uint8_t *data, uint16_t length));

    static void SetMockI2CDriver(std::shared_ptr<MockI2CDriver> mock_i2c_driver) {
        mock_i2c_driver_ = mock_i2c_driver;
    }

    static std::shared_ptr<MockI2CDriver> GetMockI2CDriver() {
        return mock_i2c_driver_;
    }

private:
    static std::shared_ptr<MockI2CDriver> mock_i2c_driver_;

};