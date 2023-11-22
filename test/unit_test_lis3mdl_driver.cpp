#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "lis3mdl_driver.hpp"
#include "i2c_driver.hpp"


using namespace testing;


class LIS3MDL_Driver_Test : public ::testing::Test {
protected:
    void SetUp() override {
        mock_i2c_driver_ = std::make_shared<MockI2CDriver>();
        MockI2CDriver::SetMockI2CDriver(mock_i2c_driver_);
    }

    void TearDown() override {
        mock_i2c_driver_.reset();
        MockI2CDriver::SetMockI2CDriver(nullptr);
    }

    std::shared_ptr<MockI2CDriver> mock_i2c_driver_;
};

TEST_F(LIS3MDL_Driver_Test, GetFullScaleConfigSucces4Gauss) {
    std::uint8_t expected_full_scale_config = 0x00;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x21, _, 1))
        .WillOnce(Invoke([expected_full_scale_config](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            buffer[0] = expected_full_scale_config << 5;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetFullScaleConfig();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(lis3mdl_driver::FullScaleConfig::k4Gauss, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetFullScaleConfigSucces8Gauss) {
    std::uint8_t expected_full_scale_config = 0x01;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x21, _, 1))
        .WillOnce(Invoke([expected_full_scale_config](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            buffer[0] = expected_full_scale_config << 5;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetFullScaleConfig();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(lis3mdl_driver::FullScaleConfig::k8Gauss, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetFullScaleConfigSucces12Gauss) {
    std::uint8_t expected_full_scale_config = 0x02;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x21, _, 1))
        .WillOnce(Invoke([expected_full_scale_config](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            buffer[0] = expected_full_scale_config << 5;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetFullScaleConfig();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(lis3mdl_driver::FullScaleConfig::k12Gauss, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetFullScaleConfigSucces16Gauss) {
    std::uint8_t expected_full_scale_config = 0x03;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x21, _, 1))
        .WillOnce(Invoke([expected_full_scale_config](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            buffer[0] = expected_full_scale_config << 5;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetFullScaleConfig();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(lis3mdl_driver::FullScaleConfig::k16Gauss, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetFullScaleConfigFailure) {
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x21, _, 1))
        .WillOnce(Return(1));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetFullScaleConfig();

    EXPECT_FALSE(return_code);
}

TEST_F(LIS3MDL_Driver_Test, GetOutputDataRateSucces0_625Hz) {
    std::uint8_t expected_output_data_rate = 0x00;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x20, _, 1))
        .WillOnce(Invoke([expected_output_data_rate](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            buffer[0] = expected_output_data_rate << 2;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetOutputDataRate();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(lis3mdl_driver::OutputDataRate::k0_625Hz, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetOutputDataRateFailure) {
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x20, _, 1))
        .WillOnce(Return(1));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetOutputDataRate();

    EXPECT_FALSE(return_code);
}

TEST_F(LIS3MDL_Driver_Test, SetOutputDataRateSucces80Hz) {
    std::uint8_t expected_output_data_rate = 0x07;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x20, _, 1))
        .WillOnce(Invoke([expected_output_data_rate](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            buffer[0] = expected_output_data_rate << 2;
            return 0;
        }));
    EXPECT_CALL(*mock_i2c_driver_, i2c_write(0x38, 0x20, _, 1))
        .WillOnce(Invoke([expected_output_data_rate](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(expected_output_data_rate << 2, buffer[0]);
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    EXPECT_TRUE(lis3mdl_driver.SetOutputDataRate(lis3mdl_driver::OutputDataRate::k80Hz));
}

TEST_F(LIS3MDL_Driver_Test, SetOutputDataRateFailure) {
    std::uint8_t expected_output_data_rate = 0x07;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, 0x20, _, 1))
        .WillOnce(Invoke([expected_output_data_rate](uint8_t, uint8_t, uint8_t *buffer, uint16_t) {
            buffer[0] = expected_output_data_rate << 2;
            return 0;
        }));
    EXPECT_CALL(*mock_i2c_driver_, i2c_write(0x38, 0x20, _, 1))
        .WillOnce(Return(1));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    EXPECT_FALSE(lis3mdl_driver.SetOutputDataRate(lis3mdl_driver::OutputDataRate::k80Hz));
}

TEST_F(LIS3MDL_Driver_Test, GetXAxisDataSucces) {
    std::int16_t expected_x_axis_data = 0x1234;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, _, _, 1)).Times(2)
        .WillOnce(Invoke([expected_x_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x28);
            buffer[0] = expected_x_axis_data & 0xFF;
            return 0;
        })).WillOnce(Invoke([expected_x_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x29);
            buffer[0] = expected_x_axis_data >> 8;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetXAxisData();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(expected_x_axis_data, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetXAxisDataFailure) {
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, _, _, 1)).Times(2)
        .WillOnce(Return(1)).WillOnce(Return(1));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetXAxisData();

    EXPECT_FALSE(return_code);
}

TEST_F(LIS3MDL_Driver_Test, GetYAxisDataSucces) {
    std::int16_t expected_y_axis_data = 0x1234;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, _, _, 1)).Times(2)
        .WillOnce(Invoke([expected_y_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x2A);
            buffer[0] = expected_y_axis_data & 0xFF;
            return 0;
        })).WillOnce(Invoke([expected_y_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x2B);
            buffer[0] = expected_y_axis_data >> 8;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetYAxisData();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(expected_y_axis_data, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetYAxisDataFailure) {
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, _, _, 1)).Times(2)
        .WillOnce(Return(1)).WillOnce(Return(1));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetYAxisData();

    EXPECT_FALSE(return_code);
}

TEST_F(LIS3MDL_Driver_Test, GetZAxisDataSucces) {
    std::int16_t expected_z_axis_data = 0x1234;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, _, _, 1)).Times(2)
        .WillOnce(Invoke([expected_z_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x2C);
            buffer[0] = expected_z_axis_data & 0xFF;
            return 0;
        })).WillOnce(Invoke([expected_z_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x2D);
            buffer[0] = expected_z_axis_data >> 8;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetZAxisData();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(expected_z_axis_data, return_code.value);
}

TEST_F(LIS3MDL_Driver_Test, GetZAxisDataFailure) {
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, _, _, 1)).Times(2)
        .WillOnce(Return(1)).WillOnce(Return(1));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetZAxisData();

    EXPECT_FALSE(return_code);
}

TEST_F(LIS3MDL_Driver_Test, GetZAxisDataSuccesNegativeValue) {
    std::int16_t expected_z_axis_data = -0x1234;
    EXPECT_CALL(*mock_i2c_driver_, i2c_read(0x38, _, _, 1)).Times(2)
        .WillOnce(Invoke([expected_z_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x2C);
            buffer[0] = expected_z_axis_data & 0xFF;
            return 0;
        })).WillOnce(Invoke([expected_z_axis_data](uint8_t, uint8_t register_address, uint8_t *buffer, uint16_t) {
            EXPECT_EQ(register_address, 0x2D);
            buffer[0] = expected_z_axis_data >> 8;
            return 0;
        }));

    lis3mdl_driver::LIS3MDL_Driver lis3mdl_driver(false);
    auto return_code = lis3mdl_driver.GetZAxisData();

    EXPECT_TRUE(return_code);
    EXPECT_EQ(expected_z_axis_data, return_code.value);
}


