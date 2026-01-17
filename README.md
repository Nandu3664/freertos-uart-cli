# FreeRTOS-Based UART Command & LED Control (Raspberry Pi Pico)

##  Project Overview
This project demonstrates a **real-time embedded system** using **FreeRTOS on Raspberry Pi Pico (RP2040)**.  
The system receives commands over **UART using interrupt-driven input**, processes them using **FreeRTOS queues**, and controls an **external LED** accordingly.

This project was developed to gain **hands-on experience with RTOS concepts**, ISR-to-task communication, and modular embedded design.

---

##  Key Features
- UART communication using **RX interrupt (ISR)**
- **Non-blocking ISR** design
- **FreeRTOS task-based architecture**
- **Queue-based inter-task communication**
- Command-based LED control (`1` → ON, `0` → OFF)
- User-friendly UART CLI menu
- Modular code structure (UART separated from application logic)



## Commands
| Command | Action |
|-------|--------|
| `1` | Turn LED ON |
| `0` | Turn LED OFF |

Example UART output:

Hello
Press 1 : LED ON
Press 0 : LED OFF

Status: LED is OFF



---

## Hardware Used
- Raspberry Pi Pico (RP2040)
- USB-to-TTL UART converter (3.3V logic)
- External LED 
- UART Terminal PuTTY 

---

## Pin Configuration
| Function | Pico GPIO |
|--------|-----------|
| UART TX | GPIO 0 |
| UART RX | GPIO 1 |
| LED    | GPIO 20 |

---

## Software Stack
- Raspberry Pi Pico SDK
- FreeRTOS Kernel
- CMake build system
- GCC ARM Embedded Toolchain


## Project Structure
freertos_uart_cli/
├── app/
│ ├── include/
│ │ ├── uart.h
│ │ └── main.h
│ └── source/
│ ├── uart.c
│ └── main.c
├── FreeRTOSConfig.h
├── CMakeLists.txt
├── pico_sdk_import.cmake
└── README.md



---

## Design Explanation

### UART RX (Interrupt Based)
- UART RX interrupt triggers when a character is received
- ISR clears the interrupt and notifies FreeRTOS
- ISR does **minimum work only** (non-blocking)

### FreeRTOS Tasks
1. **UART RX Task**
   - Waits for data from ISR
   - Sends received character to command queue

2. **Command Task**
   - Reads commands (`1` / `0`)
   - Controls LED
   - Prints status and menu via UART

---

## Key RTOS Concepts Used
- FreeRTOS Tasks
- Queues
- ISR-to-task communication
- `xHigherPriorityTaskWoken`
- Priority-based scheduling

---

## Build & Run
```Develper Command prompt 2019
mkdir build
cd build
cmake -G Ninja ..
ninja




