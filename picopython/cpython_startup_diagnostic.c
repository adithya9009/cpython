#include "pico/stdlib.h"

#include "Python.h"

#include <stdio.h>

int
main(void)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    /* Solid on means main() was reached. */
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    stdio_init_all();

    /* A short off pulse means stdio_init_all() returned. */
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    printf("BEFORE PY_INITIALIZE\r\n");
    Py_Initialize();
    printf("AFTER PY_INITIALIZE\r\n");

    for (;;) {
        sleep_ms(1000);
    }
}
