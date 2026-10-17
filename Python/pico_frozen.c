#include "Python.h"
#include "pycore_import.h"

const struct _frozen *_PyImport_FrozenBootstrap = NULL;
const struct _frozen *_PyImport_FrozenStdlib = NULL;
const struct _frozen *_PyImport_FrozenTest = NULL;
const struct _frozen *PyImport_FrozenModules = NULL;
const struct _module_alias *_PyImport_FrozenAliases = NULL;
