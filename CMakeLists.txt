cmake_minimum_required(VERSION 3.19)
set(PICO_BOARD pico_w)
set(PICO_SDK_FETCH_FROM_GIT on)

include(pico_sdk_import.cmake)
project(pico_mqtt C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
add_subdirectory(src)
