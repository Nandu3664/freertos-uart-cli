
#include"uart.h"

 /* 👇 actual memory allocation happens here */
volatile char rx_buf[CMD_BUF_SIZE];
volatile uint8_t rx_index = 0;
volatile bool cmd_ready = false;

/* UART RX ISR */
void __isr uart_rx_isr(void)
{
    while (uart_is_readable(UART_ID))
    {
        char c = uart_getc(UART_ID);

        // Echo typed character
        uart_putc(UART_ID, c);

        // End of command
        if (c == '\r' || c == '\n')
        {
            rx_buf[rx_index] = '\0';
            rx_index = 0;
            cmd_ready = true;
        }
        else
        {
            if (rx_index < CMD_BUF_SIZE - 1)
            {
                rx_buf[rx_index++] = c;
            }
        }
    }
}


 void to_uppercase(char *s)
     {
    while (*s)
       {
          if (*s >= 'a' && *s <= 'z')
            *s -= 32;
           s++;
        }
    }



void uart_initiliaze(void)
{

     uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, false);

    irq_set_exclusive_handler(UART0_IRQ, uart_rx_isr);
    irq_clear(UART0_IRQ);

    uart_set_irq_enables(UART_ID, true, false);
    irq_set_enabled(UART0_IRQ, true);

}