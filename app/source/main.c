

#include "main.h"

#define LED_PIN 20

QueueHandle_t command_queue;

/* Print CLI menu */
void print_menu(void)
{
    uart_send(
        "\r\n----------------------\r\n"
        "Press 1 : LED ON\r\n"
        "Press 0 : LED OFF\r\n"
        "----------------------\r\n"
    );
}

/* UART RX Task */
void uart_rx_task(void *param)
{
    char ch;

    uart_send("\r\nHello\r\n");
    print_menu();
    uart_send("Status: LED is OFF\r\n");

    while (1)
    {
        if (xQueueReceive(uart_rx_queue, &ch, portMAX_DELAY))
        {
            xQueueSend(command_queue, &ch, portMAX_DELAY);
        }
    }
}

/* Command Processing Task */
void command_task(void *param)
{
    char cmd;
    bool led_state = false;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    while (1)
    {
        if (xQueueReceive(command_queue, &cmd, portMAX_DELAY))
        {
            if (cmd == '1')
            {
                led_state = true;
                gpio_put(LED_PIN, 1);
                uart_send("\r\nLED turned ON\r\n");
            }
            else if (cmd == '0')
            {
                led_state = false;
                gpio_put(LED_PIN, 0);
                uart_send("\r\nLED turned OFF\r\n");
            }
            else
            {
                uart_send("\r\nInvalid command\r\n");
            }

            uart_send("Status: LED is ");
            uart_send(led_state ? "ON\r\n" : "OFF\r\n");
            print_menu();
        }
    }
}

int main(void)
{
    stdio_init_all();
    uart_initiliaze();

    command_queue = xQueueCreate(4, sizeof(char));

    xTaskCreate(uart_rx_task, "UART_RX", 512, NULL, 2, NULL);
    xTaskCreate(command_task, "CMD", 512, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);
}

