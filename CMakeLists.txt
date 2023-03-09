cmake_minimum_required(VERSION 3.16)

include(pico-sdk/pico_sdk_init.cmake)

project(capstone)

pico_sdk_init()

add_executable(dht include/DHT20-Pico/DHT20.cpp)

# Link with the pico stdlib
target_link_libraries(dht pico_stdlib hardware_adc hardware_i2c )

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(dht)

# Enable USB serial

pico_enable_stdio_uart(dht 0)
pico_enable_stdio_usb(dht 1)