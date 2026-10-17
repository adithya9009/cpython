#include "Python.h"
#include "pycore_pico.h"

#ifdef PICO_PYTHON
#  include "pico/time.h"
#endif

#include <errno.h>
#include <limits.h>

#ifndef ENOTSUP
#  define ENOTSUP EINVAL
#endif

int
_PyPico_ClockMonotonicNs(int64_t *result)
{
#ifdef PICO_PYTHON
    uint64_t usec = time_us_64();
    if (usec > (uint64_t)INT64_MAX / 1000) {
        return EOVERFLOW;
    }
    *result = (int64_t)(usec * 1000);
    return 0;
#else
    (void)result;
    return ENOTSUP;
#endif
}

int
_PyPico_ClockRealtimeNs(int64_t *result)
{
    (void)result;
    return ENOTSUP;
}

int
_PyPico_ClockResolutionNs(int monotonic, int64_t *result)
{
    if (!monotonic) {
        return ENOTSUP;
    }
    *result = 1000;
    return 0;
}
