
#ifndef UART_H
#define UART_H

#include "FreeRTOS.h"
#include "queue.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"


void uart_initiliaze(void);
void uart_send(const char *str);

/* UART RX queue handle (used by ISR) */
extern QueueHandle_t uart_rx_queue;

#endif
