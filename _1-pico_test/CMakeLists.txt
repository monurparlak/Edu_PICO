cmake_minimum_required(VERSION 3.21.2)

set(CMAKE_TOOLCHAIN_FILE D:/Main_Files/TEST_PICO_2/pico-sdk/cmake/preload/toolchains/pico_arm_gcc.cmake)

set(PICO_COPY_TO_RAM true)

set(PICO_SDK_PATH D:/Main_Files/TEST_PICO_2/pico-sdk/)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include(D:/Main_Files/TEST_PICO_2/pico-examples/pico_sdk_import.cmake)

project(SLIME)

pico_sdk_init()

add_executable(SLIME main.c)

pico_enable_stdio_usb(SLIME 1)

pico_enable_stdio_uart(SLIME 0)

target_link_libraries(SLIME pico_stdlib hardware_adc hardware_rtc hardware_uart hardware_pwm hardware_dma hardware_i2c pico_bootsel_via_double_reset pico_stdio_usb) 

target_compile_options(SLIME PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>)

set(CMAKE_CXX_STANDARD 20)

set_property(TARGET SLIME PROPERTY CXX_STANDARD 20)

pico_add_extra_outputs(SLIME)