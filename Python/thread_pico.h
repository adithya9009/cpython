#ifndef Py_THREAD_PICO_H
#define Py_THREAD_PICO_H

#include "pycore_pico.h"
#include "pycore_pythread.h"
#include "pycore_time.h"

#include <errno.h>
#include <stdlib.h>

#ifdef PICO_PYTHON
#  include "pico/sync.h"
#  include "pico/time.h"
#endif

#ifndef ENOTSUP
#  define ENOTSUP EINVAL
#endif

static void
PyThread__init_thread(void)
{
}

int
PyThread_start_joinable_thread(void (*func)(void *), void *arg,
                               PyThread_ident_t *ident,
                               PyThread_handle_t *handle)
{
    (void)func;
    (void)arg;
    (void)ident;
    (void)handle;
    errno = ENOTSUP;
    return -1;
}

int
PyThread_join_thread(PyThread_handle_t handle)
{
    (void)handle;
    errno = ENOTSUP;
    return -1;
}

int
PyThread_detach_thread(PyThread_handle_t handle)
{
    (void)handle;
    errno = ENOTSUP;
    return -1;
}

PyThread_ident_t
PyThread_get_thread_ident_ex(void)
{
    return (PyThread_ident_t)_PyPico_ThreadIdent();
}

int
PyThread_tss_create(Py_tss_t *key)
{
    if (key->_is_initialized) {
        return 0;
    }
    key->_key = PyMem_RawCalloc(1, sizeof(void *));
    if (key->_key == NULL) {
        return -1;
    }
    key->_is_initialized = 1;
    return 0;
}

void
PyThread_tss_delete(Py_tss_t *key)
{
    if (!key->_is_initialized) {
        return;
    }
    PyMem_RawFree(key->_key);
    key->_key = NULL;
    key->_is_initialized = 0;
}

int
PyThread_tss_set(Py_tss_t *key, void *value)
{
    if (!key->_is_initialized && PyThread_tss_create(key) != 0) {
        return -1;
    }
    *(void **)key->_key = value;
    return 0;
}

void *
PyThread_tss_get(Py_tss_t *key)
{
    if (!key->_is_initialized) {
        return NULL;
    }
    return *(void **)key->_key;
}

unsigned long
PyThread_get_thread_ident(void)
{
    return (unsigned long)PyThread_get_thread_ident_ex();
}

void
PyThread_exit_thread(void)
{
    for (;;) {
#ifdef PICO_PYTHON
        tight_loop_contents();
#endif
    }
}

void
PyThread_hang_thread(void)
{
    PyThread_exit_thread();
}

#define THREAD_SET_STACKSIZE(size) (-2)

#endif /* !Py_THREAD_PICO_H */
