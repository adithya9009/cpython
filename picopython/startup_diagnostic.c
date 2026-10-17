#include <stdint.h>

#include "pico/runtime.h"
#include "pico/runtime_init.h"

#define STARTUP_RESET 0x53545230u
#define STARTUP_PREINIT 0x53545231u
#define STARTUP_RUNTIME_DONE 0x53545232u
#define STARTUP_MAIN 0x53545233u

__attribute__((used, section(".data.startup_diagnostic")))
volatile uint32_t picopython_startup_state = STARTUP_RESET;

static void
startup_preinit(void)
{
    picopython_startup_state = STARTUP_PREINIT;
}

PICO_RUNTIME_INIT_FUNC(startup_preinit, PICO_RUNTIME_INIT_EARLIEST);

__attribute__((constructor(65534), used))
static void
startup_runtime_done(void)
{
    picopython_startup_state = STARTUP_RUNTIME_DONE;
}

int
main(void)
{
    picopython_startup_state = STARTUP_MAIN;
    for (;;) {
    }
}
