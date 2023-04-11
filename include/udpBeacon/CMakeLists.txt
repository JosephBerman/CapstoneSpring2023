
file(GLOB FILES *.c *.h)

add_library(udp STATIC
        ${FILES}
        )


target_compile_definitions(udp PRIVATE
        SSID="${SSID}"
        PASS="${PASS}")

target_link_libraries(udp pico_stdlib hardware_i2c pico_cyw43_arch_lwip_threadsafe_background)

target_include_directories(udp PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
