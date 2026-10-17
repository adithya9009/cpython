#include "pico/stdlib.h"

#include "Python.h"

#include <stdio.h>

int
main(void)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    stdio_init_all();
    printf("BOOT\r\n");
    printf("USB READY\r\n");
    printf("BEFORE PY_INITIALIZE\r\n");

    Py_Initialize();
    printf("AFTER PY_INITIALIZE\r\n");

    for (;;) {
        sleep_ms(1000);
    }
}
