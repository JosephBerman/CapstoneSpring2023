add_executable(threading
        main.cpp
        )




target_compile_definitions(threading PRIVATE
        SSID="$ENV{SSID}"
        PASS="$ENV{PASS}")




target_link_libraries(threading sgp
        dht
        udp
        pico_stdlib
        hardware_i2c
        pico_multicore
        pico_cyw43_arch_lwip_threadsafe_background)


target_include_directories(threading PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )



pico_add_extra_outputs(threading)

pico_enable_stdio_usb(threading 1)
pico_enable_stdio_uart(threading 0)