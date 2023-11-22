cmake_minimum_required(VERSION 3.15)

project(lis3mdl_driver CXX)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
add_subdirectory(mock)

set(DRIVER_LIVRARY_NAME ${PROJECT_NAME})

add_library(${DRIVER_LIVRARY_NAME} STATIC
        src/lis3mdl_driver.cpp)

target_include_directories(${DRIVER_LIVRARY_NAME} PUBLIC include
                                                  PRIVATE src)

target_link_libraries(${DRIVER_LIVRARY_NAME} PUBLIC i2c_driver_mock)
