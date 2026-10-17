#include "pico/stdlib.h"

#include "Python.h"

static void
busy_delay(void)
{
    for (volatile uint32_t i = 0; i < 3000000u; i++) {
        __asm volatile("nop");
    }
}

void
_PyPicoStartupMarker(unsigned int stage)
{
    unsigned int count = stage;

    for (unsigned int i = 0; i < count; i++) {
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        busy_delay();
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        busy_delay();
    }
    /* Separate each checkpoint pattern from the next one. */
    busy_delay();
    busy_delay();
    busy_delay();
}

static void
blink_pattern(unsigned int count)
{
    for (unsigned int i = 0; i < count; i++) {
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(150);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(150);
    }
    sleep_ms(750);
}

int
main(void)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    /* Two blinks mean main() ran without stdio initialization. */
    blink_pattern(2);

    Py_Initialize();

    /* Three blinks mean Py_Initialize() returned. */
    blink_pattern(3);

    for (;;) {
        sleep_ms(1000);
    }
}
