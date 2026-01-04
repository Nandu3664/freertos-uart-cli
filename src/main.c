#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    sleep_ms(2000);   // wait so PuTTY can connect

    while (1) {
        printf("UART is working\r\n");
        sleep_ms(1000);
    }
}

