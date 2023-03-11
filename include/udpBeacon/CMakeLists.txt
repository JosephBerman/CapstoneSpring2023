
add_executable(udp
        udpBeacon.c
    )

target_link_libraries(udp pico_stdlib hardware_i2c pico_cyw43_arch_lwip_threadsafe_background )


pico_add_extra_outputs(udp)

pico_enable_stdio_usb(udp 1)
pico_enable_stdio_uart(udp 0)
