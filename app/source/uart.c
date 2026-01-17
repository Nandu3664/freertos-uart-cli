
#include "uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

QueueHandle_t uart_rx_queue;

/* UART RX ISR */
void __isr uart_rx_isr(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    char ch;

    if (uart_is_readable(UART_ID))
    {
        ch = uart_getc(UART_ID);
        xQueueSendFromISR(uart_rx_queue, &ch, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void uart_initiliaze(void)
{
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, false);

    uart_rx_queue = xQueueCreate(8, sizeof(char));

    irq_set_exclusive_handler(UART0_IRQ, uart_rx_isr);
    irq_set_enabled(UART0_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);
}

void uart_send(const char *str)
{
    while (*str)
    {
        uart_putc(UART_ID, *str++);
    }
}
