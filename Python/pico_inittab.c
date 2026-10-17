#include "Python.h"

extern PyObject *PyInit__ast(void);
extern PyObject *PyInit_atexit(void);
extern PyObject *_PyWarnings_Init(void);
extern PyObject *PyMarshal_Init(void);
extern PyObject *PyInit__imp(void);

struct _inittab _PyImport_Inittab[] = {
    {"_ast", PyInit__ast},
    {"atexit", PyInit_atexit},
    {"_warnings", _PyWarnings_Init},
    {"marshal", PyMarshal_Init},
    {"_imp", PyInit__imp},
    {"builtins", NULL},
    {"sys", NULL},
    {NULL, NULL}
};
