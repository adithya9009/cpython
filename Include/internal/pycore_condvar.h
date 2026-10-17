#ifndef Py_INTERNAL_CONDVAR_H
#define Py_INTERNAL_CONDVAR_H

#ifndef Py_BUILD_CORE
#  error "this header requires Py_BUILD_CORE define"
#endif

#include "pycore_pythread.h"      // _POSIX_THREADS


#ifdef PICO_PYTHON
/*
 * Pico SDK support.  The initial port has no Python-created threads, but
 * CPython still needs mutexes and condition variables for its internals.
 */
#define Py_HAVE_CONDVAR
#define PyMUTEX_T PyPicoMutex
#define PyCOND_T PyPicoCond

int _PyPico_CondInit(PyCOND_T *cond);
int _PyPico_CondFini(PyCOND_T *cond);
int _PyPico_CondWait(PyCOND_T *cond, PyMUTEX_T *mut);
int _PyPico_CondTimedWait(PyCOND_T *cond, PyMUTEX_T *mut, long long us);
int _PyPico_CondSignal(PyCOND_T *cond);
int _PyPico_CondBroadcast(PyCOND_T *cond);

#define PyMUTEX_INIT(mut)       (mutex_init((mut)), 0)
#define PyMUTEX_FINI(mut)       0
#define PyMUTEX_LOCK(mut)       (mutex_enter_blocking((mut)), 0)
#define PyMUTEX_UNLOCK(mut)     (mutex_exit((mut)), 0)
#define PyCOND_INIT(cond)       _PyPico_CondInit(cond)
#define PyCOND_FINI(cond)       _PyPico_CondFini(cond)
#define PyCOND_SIGNAL(cond)     _PyPico_CondSignal(cond)
#define PyCOND_BROADCAST(cond)  _PyPico_CondBroadcast(cond)
#define PyCOND_WAIT(cond, mut)  _PyPico_CondWait(cond, mut)
#define PyCOND_TIMEDWAIT(cond, mut, us) \
    _PyPico_CondTimedWait(cond, mut, us)

#elif defined(_POSIX_THREADS)
/*
 * POSIX support
 */
#define Py_HAVE_CONDVAR

#ifdef HAVE_PTHREAD_H
#  include <pthread.h>            // pthread_mutex_t
#endif

#define PyMUTEX_T pthread_mutex_t
#define PyCOND_T pthread_cond_t

#elif defined(NT_THREADS)
/*
 * Windows (XP, 2003 server and later, as well as (hopefully) CE) support
 *
 * Emulated condition variables ones that work with XP and later, plus
 * example native support on VISTA and onwards.
 */
#define Py_HAVE_CONDVAR

/* include windows if it hasn't been done before */
#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>              // CRITICAL_SECTION

/* options */
/* emulated condition variables are provided for those that want
 * to target Windows XP or earlier. Modify this macro to enable them.
 */
#ifndef _PY_EMULATED_WIN_CV
#define _PY_EMULATED_WIN_CV 0  /* use non-emulated condition variables */
#endif

/* fall back to emulation if targeting earlier than Vista */
#if !defined NTDDI_VISTA || NTDDI_VERSION < NTDDI_VISTA
#undef _PY_EMULATED_WIN_CV
#define _PY_EMULATED_WIN_CV 1
#endif

#if _PY_EMULATED_WIN_CV

typedef CRITICAL_SECTION PyMUTEX_T;

/* The ConditionVariable object.  From XP onwards it is easily emulated
   with a Semaphore.
   Semaphores are available on Windows XP (2003 server) and later.
   We use a Semaphore rather than an auto-reset event, because although
   an auto-reset event might appear to solve the lost-wakeup bug (race
   condition between releasing the outer lock and waiting) because it
   maintains state even though a wait hasn't happened, there is still
   a lost wakeup problem if more than one thread are interrupted in the
   critical place.  A semaphore solves that, because its state is
   counted, not Boolean.
   Because it is ok to signal a condition variable with no one
   waiting, we need to keep track of the number of
   waiting threads.  Otherwise, the semaphore's state could rise
   without bound.  This also helps reduce the number of "spurious wakeups"
   that would otherwise happen.
 */

typedef struct _PyCOND_T
{
    HANDLE sem;
    int waiting; /* to allow PyCOND_SIGNAL to be a no-op */
} PyCOND_T;

#else /* !_PY_EMULATED_WIN_CV */

/* Use native Windows primitives if build target is Vista or higher */

/* SRWLOCK is faster and better than CriticalSection */
typedef SRWLOCK PyMUTEX_T;

typedef CONDITION_VARIABLE  PyCOND_T;

#endif /* _PY_EMULATED_WIN_CV */

#endif /* _POSIX_THREADS, NT_THREADS */

#endif /* Py_INTERNAL_CONDVAR_H */
