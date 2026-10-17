#include "Python.h"
#include "pycore_initconfig.h"

PyStatus
_PyConfig_InitPathConfig(PyConfig *config, int compute_path_config)
{
    (void)compute_path_config;
    config->module_search_paths_set = 1;
    return PyStatus_Ok();
}
