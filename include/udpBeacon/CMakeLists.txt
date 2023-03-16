
add_executable(udp
        udpBeacon.c
        )


target_compile_definitions(udp PRIVATE
        SSID="${SSID}"
        PASS="${PASS}")

target_link_libraries(udp pico_stdlib hardware_i2c pico_cyw43_arch_lwip_threadsafe_background)

target_include_directories(udp PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )


pico_add_extra_outputs(udp)

pico_enable_stdio_usb(udp 1)
pico_enable_stdio_uart(udp 0)
