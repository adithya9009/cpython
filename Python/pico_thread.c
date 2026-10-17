#include "Python.h"
#include "pycore_pico.h"

#ifdef PICO_PYTHON
#  include "pico/sync.h"
#  include <stdbool.h>
#endif

#include <errno.h>

#ifndef ENOTSUP
#  define ENOTSUP EINVAL
#endif

unsigned long long
_PyPico_ThreadIdent(void)
{
    return 1;
}

int
_PyPico_ThreadStart(void (*func)(void *), void *arg,
                    unsigned long long *ident,
                    unsigned long long *handle)
{
    (void)func;
    (void)arg;
    (void)ident;
    (void)handle;
    return ENOTSUP;
}

int
_PyPico_ThreadJoin(unsigned long long handle)
{
    (void)handle;
    return ENOTSUP;
}

int
_PyPico_ThreadDetach(unsigned long long handle)
{
    (void)handle;
    return ENOTSUP;
}

#ifdef PICO_PYTHON
int
_PyPico_CondInit(semaphore_t *cond)
{
    sem_init(cond, 0, 0);
    return 0;
}

int
_PyPico_CondFini(semaphore_t *cond)
{
    (void)cond;
    return 0;
}

int
_PyPico_CondWait(semaphore_t *cond, mutex_t *mutex)
{
    mutex_exit(mutex);
    (void)sem_acquire_blocking(cond);
    mutex_enter_blocking(mutex);
    return 0;
}

int
_PyPico_CondTimedWait(semaphore_t *cond, mutex_t *mutex,
                      long long microseconds)
{
    bool acquired;
    mutex_exit(mutex);
    acquired = microseconds < 0
        ? (sem_acquire_blocking(cond), true)
        : sem_acquire_timeout_us(cond, (uint64_t)microseconds);
    mutex_enter_blocking(mutex);
    return acquired ? 0 : 1;
}

int
_PyPico_CondSignal(semaphore_t *cond)
{
    sem_release(cond);
    return 0;
}

int
_PyPico_CondBroadcast(semaphore_t *cond)
{
    sem_release(cond);
    return 0;
}
#endif
