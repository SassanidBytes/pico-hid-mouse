cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(pico_hid C CXX ASM)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_executable(pico_hid main.c)

target_link_libraries(pico_hid
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(pico_hid)