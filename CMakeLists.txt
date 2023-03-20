cmake_minimum_required(VERSION 3.16)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(pico-sdk/pico_sdk_init.cmake)

project(capstone)

pico_sdk_init()



include_directories(include/DHT20-Pico)
include_directories(include/udpBeacon)

add_subdirectory(include/DHT20-Pico)
add_subdirectory(include/udpBeacon)
add_subdirectory(src)




