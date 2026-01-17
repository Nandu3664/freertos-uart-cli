cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

include(FreeRTOS_Kernel_import.cmake)

project(uart_baremetal C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()


add_executable(uart_baremetal
    app/source/main.c
)

target_sources(uart_baremetal PRIVATE
    app/source/uart.c
)
target_include_directories(uart_baremetal PRIVATE
    app/include
    ${CMAKE_CURRENT_LIST_DIR}
    
)

target_link_libraries(uart_baremetal pico_stdlib
pico_async_context_freertos
    FreeRTOS-Kernel-Heap4)

pico_enable_stdio_uart(uart_baremetal 1)
pico_enable_stdio_usb(uart_baremetal 0)

pico_add_extra_outputs(uart_baremetal)


