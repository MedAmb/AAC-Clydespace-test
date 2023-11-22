#ifndef LIS3MDL_CONSTANTS_HPP_
#define LIS3MDL_CONSTANTS_HPP_

#include <cstdint>

namespace lis3mdl_driver {

constexpr std::uint8_t kDeviceAddressLow{0x38};
constexpr std::uint8_t kDeviceAddressHigh{0x3C};

constexpr std::uint8_t kControlRegister1{0x20};

constexpr std::uint8_t kOutputDataRateOffset{2};
constexpr std::uint8_t kOutputDataRateMask{0x07};

constexpr std::uint8_t kControlRegister2{0x21};

constexpr std::uint8_t kFullScaleOffset{5};
constexpr std::uint8_t kFullScaleMask{0x03};


constexpr std::uint8_t kXAxisDataLowRegister{0x28};
constexpr std::uint8_t kXAxisDataHighRegister{0x29};

constexpr std::uint8_t kYAxisDataLowRegister{0x2A};
constexpr std::uint8_t kYAxisDataHighRegister{0x2B};

constexpr std::uint8_t kZAxisDataLowRegister{0x2C};
constexpr std::uint8_t kZAxisDataHighRegister{0x2D};

} // namespace lis3mdl_driver

#endif // LIS3MDL_CONSTANTS_HPP_

