
#include"main.h"

int main(void)
{
    uart_initiliaze();
    
    uart_puts(UART_ID, "\r\nType ON or OFF\r\n");

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
