cmake_minimum_required(VERSION 3.16)

include(pico-sdk/pico_sdk_init.cmake)

project(capstone)

pico_sdk_init()

add_executable(dht include/DHT20-Pico/DHT20.cpp)
add_executable(udp include/udpBeacon/udpBeacon.c)




# Link with the pico stdlib
target_link_libraries(dht pico_stdlib hardware_i2c)
target_link_libraries(udp pico_stdlib hardware_i2c pico_cyw43_arch_lwip_threadsafe_background )


target_include_directories(dht PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )
target_include_directories(udp PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )



# Create map/bin/hex/uf2 files
pico_add_extra_outputs(dht)
pico_add_extra_outputs(udp)

# Enable USB serial

pico_enable_stdio_uart(dht 0)
pico_enable_stdio_usb(dht 1)


pico_enable_stdio_usb(udp 1)
pico_enable_stdio_uart(udp 0)

