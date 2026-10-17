#ifndef Py_INTERNAL_PICO_H
#define Py_INTERNAL_PICO_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef Py_BUILD_CORE
#  error "this header requires Py_BUILD_CORE define"
#endif

#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include "pyport.h"

/* PicoPython platform hooks.  Implementations live in Python/pico_*.c. */

int _PyPico_ClockMonotonicNs(int64_t *result);
int _PyPico_ClockRealtimeNs(int64_t *result);
int _PyPico_ClockResolutionNs(int monotonic, int64_t *result);

int _PyPico_Open(const char *path, int flags, int mode, int *fd);
int _PyPico_Close(int fd);
Py_ssize_t _PyPico_Read(int fd, void *buffer, size_t size);
Py_ssize_t _PyPico_Write(int fd, const void *buffer, size_t size);
int _PyPico_IsValidFD(int fd);
int _PyPico_IsTTY(int fd);
int _PyPico_GetCwd(char *buffer, size_t size);
const char *_PyPico_StrError(int error);

int _PyPico_ThreadStart(void (*func)(void *), void *arg,
                        unsigned long long *ident,
                        unsigned long long *handle);
int _PyPico_ThreadJoin(unsigned long long handle);
int _PyPico_ThreadDetach(unsigned long long handle);
unsigned long long _PyPico_ThreadIdent(void);

#ifdef __cplusplus
}
#endif

#endif /* !Py_INTERNAL_PICO_H */
