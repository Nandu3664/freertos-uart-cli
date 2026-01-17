#ifndef UART_H
#define UART_H

#include "hardware/uart.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include <string.h>


#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define CMD_BUF_SIZE 16

 
extern volatile char rx_buf[CMD_BUF_SIZE];
extern volatile uint8_t rx_index;
extern volatile bool cmd_ready;




void uart_initiliaze(void);
void __isr uart_rx_isr(void);
void to_uppercase(char *s);

#endif /* UART_H */