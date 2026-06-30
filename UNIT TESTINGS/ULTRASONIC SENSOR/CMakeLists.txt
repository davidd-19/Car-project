cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_FETCH_FROM_GIT 1)

include(pico_sdk_import.cmake)

project(pico-projects)

pico_sdk_init()

add_executable(blink_led
    blink_led.c
    Ultrasonic.c
)

target_include_directories(blink_led PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(blink_led
    pico_multicore
    pico_stdlib
)

pico_enable_stdio_usb(blink_led 1)
pico_enable_stdio_uart(blink_led 0)

pico_add_extra_outputs(blink_led)