#include <stdint.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/runtime.h"
#include "pico/runtime_init.h"

static void
delay_without_runtime_services(void)
{
    for (volatile uint32_t i = 0; i < 2000000u; i++) {
        __asm volatile("nop");
    }
}

static void
show_stage(uint count)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);

    for (uint blink = 0; blink < count; blink++) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        delay_without_runtime_services();
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        delay_without_runtime_services();
    }
}

static void
startup_preinit(void)
{
    show_stage(1);
}

PICO_RUNTIME_INIT_FUNC(startup_preinit, PICO_RUNTIME_INIT_EARLIEST);

__attribute__((constructor(65534), used))
static void
startup_runtime_done(void)
{
    show_stage(2);
}

int
main(void)
{
    show_stage(3);
    for (;;) {
    }
}
