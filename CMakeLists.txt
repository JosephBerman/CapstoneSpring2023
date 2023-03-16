cmake_minimum_required(VERSION 3.16)

include(pico-sdk/pico_sdk_init.cmake)

project(capstone)

pico_sdk_init()




add_subdirectory(include/DHT20-Pico)
add_subdirectory(include/udpBeacon)





