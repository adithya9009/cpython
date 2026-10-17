#include "Python.h"
#include "pycore_object.h"
#include "pycore_unicodeobject.h"
#include "pycore_pico.h"

#include "pico/stdio.h"
#include <errno.h>
#include <limits.h>
#include <string.h>

#ifndef ENOTSUP
#  define ENOTSUP EINVAL
#endif

int
_PyPico_Open(const char *path, int flags, int mode, int *fd)
{
    (void)path;
    (void)flags;
    (void)mode;
    (void)fd;
    errno = ENOTSUP;
    return -1;
}

int
_PyPico_Close(int fd)
{
    (void)fd;
    errno = ENOTSUP;
    return -1;
}

int
_Py_open_noraise(const char *pathname, int flags)
{
    (void)pathname;
    (void)flags;
    errno = ENOTSUP;
    return -1;
}

int
_Py_dup(int fd)
{
    (void)fd;
    errno = ENOTSUP;
    return -1;
}

Py_ssize_t
_PyPico_Read(int fd, void *buffer, size_t size)
{
    (void)fd;
    (void)buffer;
    (void)size;
    errno = ENOTSUP;
    return -1;
}

Py_ssize_t
_PyPico_Write(int fd, const void *buffer, size_t size)
{
    if (fd != 1 && fd != 2) {
        errno = ENOTSUP;
        return -1;
    }
    if (size > INT_MAX) {
        errno = EINVAL;
        return -1;
    }
    if (stdio_put_string((const char *)buffer, (int)size, false, false) < 0) {
        errno = EIO;
        return -1;
    }
    return (Py_ssize_t)size;
}

Py_ssize_t
_Py_write_noraise(int fd, const void *buffer, size_t size)
{
    int saved_errno = errno;
    Py_ssize_t result = _PyPico_Write(fd, buffer, size);
    errno = saved_errno;
    return result;
}

Py_ssize_t
_Py_write(int fd, const void *buffer, size_t size)
{
    return _PyPico_Write(fd, buffer, size);
}

int
_PyPico_IsValidFD(int fd)
{
    (void)fd;
    return 0;
}

int
_PyPico_IsTTY(int fd)
{
    (void)fd;
    return 0;
}

int
_PyPico_GetCwd(char *buffer, size_t size)
{
    (void)buffer;
    (void)size;
    errno = ENOTSUP;
    return -1;
}

const char *
_PyPico_StrError(int error)
{
    if (error == ENOTSUP) {
        return "operation not supported by the Pico platform layer";
    }
    return strerror(error);
}
#undef PyOS_FSPath
PyObject *
PyOS_FSPath(PyObject *path)
{
    PyObject *func;
    PyObject *path_repr;

    if (PyUnicode_Check(path) || PyBytes_Check(path)) {
        return Py_NewRef(path);
    }

    func = _PyObject_LookupSpecial(path, &_Py_ID(__fspath__));
    if (func == NULL || func == Py_None) {
        return PyErr_Format(PyExc_TypeError,
                            "expected str, bytes or os.PathLike object, "
                            "not %.200s",
                            _PyType_Name(Py_TYPE(path)));
    }

    path_repr = PyObject_CallNoArgs(func);
    Py_DECREF(func);
    if (path_repr == NULL) {
        return NULL;
    }
    if (!PyUnicode_Check(path_repr) && !PyBytes_Check(path_repr)) {
        PyErr_Format(PyExc_TypeError,
                     "expected %.200s.__fspath__() to return str or bytes, "
                     "not %.200s", _PyType_Name(Py_TYPE(path)),
                     _PyType_Name(Py_TYPE(path_repr)));
        Py_DECREF(path_repr);
        return NULL;
    }
    return path_repr;
}
