cmake_minimum_required(VERSION 3.19)
set(PICO_BOARD pico_w)
set(PICO_SDK_FETCH_FROM_GIT on)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(pico_mqtt C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()


add_executable(pico_mqtt main2.c)
target_include_directories(pico_mqtt PRIVATE ${CMAKE_SOURCE_DIR}/include)




# Enable USB output for debugging (if needed)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)


# Link required libraries
target_link_libraries(pico_mqtt 
    pico_stdlib
    hardware_gpio
    pico_cyw43_arch_lwip_threadsafe_background # requires headerfile in include folder lwipopts
    #pico_cyw43_arch_none couldnt build w this(some header problem)
    hardware_i2c
)

pico_add_extra_outputs(pico_mqtt)
