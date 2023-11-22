#include "lis3mdl_driver.hpp"

#include "i2c_driver.hpp"

#include "lis3mdl_constants.hpp"

namespace lis3mdl_driver {

LIS3MDL_Driver::LIS3MDL_Driver(bool is_SDO_high)
    : device_address_{is_SDO_high ? kDeviceAddressHigh : kDeviceAddressLow} {}

ReturnCode<FullScaleConfig> LIS3MDL_Driver::GetFullScaleConfig() const {

  ReturnCode<FullScaleConfig> result{FullScaleConfig::k4Gauss, false};
  auto control_register_2 = ReadRegister(kControlRegister2);

  if (control_register_2) {
    result.success = true;
    result.value = static_cast<FullScaleConfig>(ExtractValueFromRegister(
        control_register_2.value, kFullScaleOffset, kFullScaleMask));
  }

  return result;
}

ReturnCode<OutputDataRate> LIS3MDL_Driver::GetOutputDataRate() const {

  ReturnCode<OutputDataRate> result{OutputDataRate::k0_625Hz, false};
  auto control_register_1 = ReadRegister(kControlRegister1);

  if (control_register_1) {
    result.success = true;
    result.value = static_cast<OutputDataRate>(ExtractValueFromRegister(
        control_register_1.value, kOutputDataRateOffset, kOutputDataRateMask));
  }

  return result;
}

bool LIS3MDL_Driver::SetOutputDataRate(OutputDataRate output_data_rate) const {

  auto control_register_1 = ReadRegister(kControlRegister1);

  if (control_register_1) {
    auto new_control_register_1 =
        InsertValueIntoRegister(control_register_1.value, kOutputDataRateOffset,
                                static_cast<std::uint8_t>(output_data_rate));

    return WriteRegister(kControlRegister1, new_control_register_1);
  }

  return false;
}

ReturnCode<std::int16_t> LIS3MDL_Driver::GetXAxisData() const {

  ReturnCode<std::int16_t> result{0, false};
  auto x_axis_data_low = ReadRegister(kXAxisDataLowRegister);
  auto x_axis_data_high = ReadRegister(kXAxisDataHighRegister);

  if (x_axis_data_low && x_axis_data_high) {
    result.success = true;
    result.value = DecodeTwosComplement(
        CombineRegisters(x_axis_data_low.value, x_axis_data_high.value), 16);
  }

  return result;
}

ReturnCode<std::int16_t> LIS3MDL_Driver::GetYAxisData() const {

  ReturnCode<std::int16_t> result{0, false};
  auto y_axis_data_low = ReadRegister(kYAxisDataLowRegister);
  auto y_axis_data_high = ReadRegister(kYAxisDataHighRegister);

  if (y_axis_data_low && y_axis_data_high) {
    result.success = true;
    result.value = DecodeTwosComplement(
        CombineRegisters(y_axis_data_low.value, y_axis_data_high.value), 16);
  }

  return result;
}

ReturnCode<std::int16_t> LIS3MDL_Driver::GetZAxisData() const {

  ReturnCode<std::int16_t> result{0, false};
  auto z_axis_data_low = ReadRegister(kZAxisDataLowRegister);
  auto z_axis_data_high = ReadRegister(kZAxisDataHighRegister);

  if (z_axis_data_low && z_axis_data_high) {
    result.success = true;
    result.value = DecodeTwosComplement(
        CombineRegisters(z_axis_data_low.value, z_axis_data_high.value), 16);
  }

  return result;
}

bool LIS3MDL_Driver::WriteRegister(std::uint8_t register_address,
                                   std::uint8_t data) const {
    auto write_result = i2c_write(device_address_, register_address, &data, 1);

    return write_result == 0;
}

ReturnCode<std::uint8_t>
LIS3MDL_Driver::ReadRegister(std::uint8_t register_address) const {

    std::uint8_t buffer{0};
    auto read_result =
        i2c_read(device_address_, register_address, &buffer, 1);

    return {buffer, read_result == 0};
}

std::uint8_t LIS3MDL_Driver::ExtractValueFromRegister(
    std::uint8_t register_value, std::uint8_t offset, std::uint8_t mask) const {
  return (register_value >> offset) & mask;
}

std::uint8_t
LIS3MDL_Driver::InsertValueIntoRegister(std::uint8_t register_value,
                                        std::uint8_t offset,
                                        std::uint8_t value) const {
  return register_value | (value << offset);
}

std::uint16_t
LIS3MDL_Driver::CombineRegisters(std::uint8_t low_register,
                                 std::uint8_t high_register) const {
  return (static_cast<std::int16_t>(high_register) << 8) | low_register;
}

std::int16_t LIS3MDL_Driver::DecodeTwosComplement(std::uint16_t value,
                                                  std::uint8_t number_of_bits) const {
  if (value & (1 << (number_of_bits - 1))) {
    value -= 1 << number_of_bits;
  }

  return value;
}



} // namespace lis3mdl_driver