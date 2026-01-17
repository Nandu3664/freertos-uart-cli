


#include"main.h"
/* UART FreeRTOS task */
void uart_task(void *param)
{
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
                uart_puts(UART_ID, "\r\n FreeRTos based OFF\r\n");
            }
            else
            {
                uart_puts(UART_ID, "\r\nUnknown Command\r\n");
            }
        }
    }
}





int main(void)
{
    uart_initiliaze();
    
    uart_puts(UART_ID, "\r\nType ON or OFF\r\n");

    /* Create UART task */
    xTaskCreate(
        uart_task,
        "UART_Task",
        512,
        NULL,
        2,
        NULL
    );

    /* Start scheduler */
    vTaskStartScheduler();

    while (1)
    {
        tight_loop_contents();
    }

   
}

