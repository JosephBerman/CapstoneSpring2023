cmake_minimum_required(VERSION 3.16)

include(pico-sdk/pico_sdk_init.cmake)

project(Capstone)

pico_sdk_init()

add_executable(Capstone )

# Link with the pico stdlib
target_link_libraries(Capstone pico_stdlib hardware_adc)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(Capstone)

# Enable USB serial
pico_enable_stdio_usb(Capstone 1)
pico_enable_stdio_uart(Capstone 0)