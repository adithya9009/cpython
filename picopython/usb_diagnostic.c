#include "pico/stdlib.h"

int
main(void)
{
    stdio_init_all();

    for (;;) {
        printf("USB DIAGNOSTIC OK\r\n");
        sleep_ms(1000);
    }
}
