// #include <stdio.h>
// #include "pico/stdlib.h"

// int main() {
//     stdio_init_all();

//     sleep_ms(2000);   // wait so PuTTY can connect

//     while (1) {
//         printf("UART is working\r\n");
//         sleep_ms(1000);
//     }
// }


// #include "pico/stdlib.h"
// #include "hardware/uart.h"
// #include "hardware/irq.h"

// #define UART_ID uart0
// #define BAUD_RATE 115200

// #define UART_TX_PIN 0
// #define UART_RX_PIN 1

// // RX interrupt handler
// void __isr uart_rx_isr(void)
// {
//     while (uart_is_readable(UART_ID))
//     {
//         uint8_t ch = uart_getc(UART_ID);
//         uart_putc(UART_ID, ch);   // echo back
//         // Startup message
//         uart_puts(UART_ID, "\r\nUART RX Interrupt Echo Ready\r\n");
//     }
// }

// int main(void)
// {
//     // Init UART
//     uart_init(UART_ID, BAUD_RATE);

//     // Set pins
//     gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
//     gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

//     // Explicit UART format (VERY IMPORTANT)
//     uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);

//     // Disable FIFO for simple ISR behavior
//     uart_set_fifo_enabled(UART_ID, false);

//     // Clear any pending UART IRQ
//     irq_clear(UART0_IRQ);

//     // Register ISR
//     irq_set_exclusive_handler(UART0_IRQ, uart_rx_isr);

//     // Enable RX interrupt at UART level
//     uart_set_irq_enables(UART_ID, true, false);

//     // Enable IRQ at NVIC level
//     irq_set_enabled(UART0_IRQ, true);

//     // Startup message
//     uart_puts(UART_ID, "\r\nUART RX Interrupt Echo Ready\r\n");

//     while (1)
//     {
//         tight_loop_contents();
//     }
// }



#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include <string.h>

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define CMD_BUF_SIZE 16

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

int main(void)
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

    uart_puts(UART_ID, "\r\nType ON or OFF\r\n");
    void to_uppercase(char *s)
     {
    while (*s)
       {
          if (*s >= 'a' && *s <= 'z')
            *s -= 32;
           s++;
        }
    }


    while (1)
    {
        if (cmd_ready)
        {
            cmd_ready = false;
            to_uppercase((char *)rx_buf);
             
            if (strcmp((char *)rx_buf, "ON") == 0)
            {
                uart_puts(UART_ID, "\r\nON\r\n");
            }
            else if (strcmp((char *)rx_buf, "OFF") == 0)
            {
                uart_puts(UART_ID, "\r\nOFF\r\n");
            }
            else
            {
                uart_puts(UART_ID, "\r\nUnknown Command\r\n");
            }
        }
    }
}
