#include "pico/stdlib.h"

#include <stdio.h>

int
main(void)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    stdio_init_all();

    for (;;) {
        printf("USB OK\r\n");
        sleep_ms(1000);
    }
}
