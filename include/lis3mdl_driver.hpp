#ifndef LIS3MDL_DRIVER_HPP_
#define LIS3MDL_DRIVER_HPP_

#include <cstdint>

namespace lis3mdl_driver {

template <typename T>

struct ReturnCode {
    T value;
    bool success;

    operator bool() const {
        return success;
    }
};

enum class FullScaleConfig : std::uint8_t {
    k4Gauss = 0x00,
    k8Gauss = 0x01,
    k12Gauss = 0x02,
    k16Gauss = 0x03
};

enum class OutputDataRate : std::uint8_t {
    k0_625Hz = 0x00,
    k1_25Hz = 0x01,
    k2_5Hz = 0x02,
    k5Hz = 0x03,
    k10Hz = 0x04,
    k20Hz = 0x05,
    k40Hz = 0x06,
    k80Hz = 0x07
};

class LIS3MDL_Driver {
public:
    explicit LIS3MDL_Driver(bool is_SDO_high);
    LIS3MDL_Driver(const LIS3MDL_Driver&) = delete;
    LIS3MDL_Driver& operator=(const LIS3MDL_Driver&) = delete;
    LIS3MDL_Driver(LIS3MDL_Driver&&) = delete;
    LIS3MDL_Driver& operator=(LIS3MDL_Driver&&) = delete;

    ~LIS3MDL_Driver() = default;

    ReturnCode<FullScaleConfig> GetFullScaleConfig() const;

    ReturnCode<OutputDataRate> GetOutputDataRate() const;
    bool SetOutputDataRate(OutputDataRate) const;

    bool EnableInterruptPin() const;
    bool DisableInterruptPin() const;

    ReturnCode<std::int16_t> GetXAxisData() const;
    ReturnCode<std::int16_t> GetYAxisData() const;
    ReturnCode<std::int16_t> GetZAxisData() const;

private:
    const std::uint8_t device_address_;

    bool WriteRegister(std::uint8_t register_address, std::uint8_t data) const;
    ReturnCode<std::uint8_t> ReadRegister(std::uint8_t register_address) const;
    std::uint8_t ExtractValueFromRegister(std::uint8_t register_value, std::uint8_t offset, std::uint8_t mask) const;
    std::uint8_t InsertValueIntoRegister(std::uint8_t register_value, std::uint8_t offset, std::uint8_t value) const;
    std::uint16_t CombineRegisters(std::uint8_t low_register, std::uint8_t high_register) const;
    std::int16_t DecodeTwosComplement(std::uint16_t value, std::uint8_t number_of_bits) const;
};

} // namespace lis3mdl_driver

#endif /* LIS3MDL_DRIVER_HPP_ */