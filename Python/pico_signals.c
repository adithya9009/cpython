#include "Python.h"
#include "pycore_pystate.h"
#include "pycore_pyerrors.h"

int
_PyErr_CheckSignalsTstate(PyThreadState *tstate)
{
    (void)tstate;
    return 0;
}

int
_PyErr_CheckSignals(void)
{
    return 0;
}

int
PyErr_CheckSignals(void)
{
    return 0;
}

int
_PySignal_Init(int install_signal_handlers)
{
    (void)install_signal_handlers;
    return 0;
}

void
_PySignal_Fini(void)
{
}

int
_PyOS_InterruptOccurred(PyThreadState *tstate)
{
    (void)tstate;
    return 0;
}

int
PyOS_InterruptOccurred(void)
{
    return 0;
}
