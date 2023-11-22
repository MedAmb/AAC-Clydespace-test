project(i2c_driver_mock CXX)

add_library(i2c_driver_mock STATIC
    i2c_driver.cpp
)

target_include_directories(i2c_driver_mock PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(i2c_driver_mock PUBLIC
    gmock
)