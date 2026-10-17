cmake_minimum_required(VERSION 3.20)

set(PICO_BOARD pico2 CACHE STRING "Pico board")
set(PICO_PLATFORM rp2350 CACHE STRING "Pico platform")
set(PICO_COMPILER pico_arm_cortex_m33_gcc CACHE STRING "Pico compiler")
set(PICO_NO_PICOTOOL ON CACHE BOOL "Do not build host picotool for this probe")

if (NOT DEFINED ENV{PICO_SDK_PATH} AND NOT PICO_SDK_PATH)
    set(PICO_SDK_PATH "C:/Users/adith/picoprojects/pico-sdk")
endif()

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(picopython_stage2 C CXX ASM)

pico_sdk_init()

set(CPYTHON_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(PICOPYTHON_SOURCES
    "${CPYTHON_ROOT}/Python/pico_fileutils.c"
    "${CPYTHON_ROOT}/Python/pico_time.c"
    "${CPYTHON_ROOT}/Python/pico_thread.c"
    "${CPYTHON_ROOT}/Python/pico_signals.c"
    "${CPYTHON_ROOT}/Python/pico_inittab.c"
    "${CPYTHON_ROOT}/Python/pico_pathconfig.c"
    "${CPYTHON_ROOT}/Python/pytime.c"
    "${CPYTHON_ROOT}/Python/thread.c"
    "${CPYTHON_ROOT}/Python/fileutils.c"
    "${CPYTHON_ROOT}/Python/marshal.c"
    "${CPYTHON_ROOT}/Python/getversion.c"
    "${CPYTHON_ROOT}/Python/bootstrap_hash.c"
    "${CPYTHON_ROOT}/Python/dtoa.c"
    "${CPYTHON_ROOT}/Python/getopt.c"
    "${CPYTHON_ROOT}/Python/crossinterp.c"
    "${CPYTHON_ROOT}/Python/hashtable.c"
    "${CPYTHON_ROOT}/Python/slots.c"
    "${CPYTHON_ROOT}/Python/slots_generated.c"
    "${CPYTHON_ROOT}/Python/structmember.c"
    "${CPYTHON_ROOT}/Python/pyctype.c"
    "${CPYTHON_ROOT}/Python/pystrhex.c"
    "${CPYTHON_ROOT}/Python/mysnprintf.c"
    "${CPYTHON_ROOT}/Python/mystrtoul.c"
    "${CPYTHON_ROOT}/Parser/myreadline.c"
    "${CPYTHON_ROOT}/Python/pico_frozen.c"
    "${CPYTHON_ROOT}/Python/importdl.c"
    "${CPYTHON_ROOT}/Python/gc_gil.c"
    "${CPYTHON_ROOT}/Python/ast_preprocess.c"
    "${CPYTHON_ROOT}/Python/ast_unparse.c"
    "${CPYTHON_ROOT}/Python/future.c"
    "${CPYTHON_ROOT}/Python/getplatform.c"
    "${CPYTHON_ROOT}/Python/getcopyright.c"
    "${CPYTHON_ROOT}/Python/getcompiler.c"
    "${CPYTHON_ROOT}/Modules/getbuildinfo.c"
    "${CPYTHON_ROOT}/Modules/_datetimemodule.c"
    "${CPYTHON_ROOT}/Python/assemble.c"
    "${CPYTHON_ROOT}/Python/codegen.c"
    "${CPYTHON_ROOT}/Python/flowgraph.c"
    "${CPYTHON_ROOT}/Python/instruction_sequence.c"
    "${CPYTHON_ROOT}/Python/pystate.c"
    "${CPYTHON_ROOT}/Python/ceval.c"
    "${CPYTHON_ROOT}/Python/instrumentation.c"
    "${CPYTHON_ROOT}/Python/intrinsics.c"
    "${CPYTHON_ROOT}/Python/optimizer.c"
    "${CPYTHON_ROOT}/Python/suggestions.c"
    "${CPYTHON_ROOT}/Python/specialize.c"
    "${CPYTHON_ROOT}/Python/sysmodule.c"
    "${CPYTHON_ROOT}/Python/traceback.c"
    "${CPYTHON_ROOT}/Python/pylifecycle.c"
    "${CPYTHON_ROOT}/Python/initconfig.c"
    "${CPYTHON_ROOT}/Python/preconfig.c"
    "${CPYTHON_ROOT}/Python/context.c"
    "${CPYTHON_ROOT}/Python/hamt.c"
    "${CPYTHON_ROOT}/Python/getargs.c"
    "${CPYTHON_ROOT}/Python/modsupport.c"
    "${CPYTHON_ROOT}/Python/import.c"
    "${CPYTHON_ROOT}/Python/pythonrun.c"
    "${CPYTHON_ROOT}/Python/errors.c"
    "${CPYTHON_ROOT}/Python/gc.c"
    "${CPYTHON_ROOT}/Python/lock.c"
    "${CPYTHON_ROOT}/Python/parking_lot.c"
    "${CPYTHON_ROOT}/Python/ceval_gil.c"
    "${CPYTHON_ROOT}/Python/critical_section.c"
    "${CPYTHON_ROOT}/Python/frame.c"
    "${CPYTHON_ROOT}/Objects/object.c"
    "${CPYTHON_ROOT}/Objects/obmalloc.c"
    "${CPYTHON_ROOT}/Objects/dictobject.c"
    "${CPYTHON_ROOT}/Objects/exceptions.c"
    "${CPYTHON_ROOT}/Objects/listobject.c"
    "${CPYTHON_ROOT}/Objects/boolobject.c"
    "${CPYTHON_ROOT}/Objects/frameobject.c"
    "${CPYTHON_ROOT}/Objects/call.c"
    "${CPYTHON_ROOT}/Objects/abstract.c"
    "${CPYTHON_ROOT}/Objects/moduleobject.c"
    "${CPYTHON_ROOT}/Objects/codeobject.c"
    "${CPYTHON_ROOT}/Objects/fileobject.c"
    "${CPYTHON_ROOT}/Objects/templateobject.c"
    "${CPYTHON_ROOT}/Objects/interpolationobject.c"
    "${CPYTHON_ROOT}/Objects/floatobject.c"
    "${CPYTHON_ROOT}/Objects/setobject.c"
    "${CPYTHON_ROOT}/Objects/bytearrayobject.c"
    "${CPYTHON_ROOT}/Objects/memoryobject.c"
    "${CPYTHON_ROOT}/Objects/cellobject.c"
    "${CPYTHON_ROOT}/Objects/funcobject.c"
    "${CPYTHON_ROOT}/Objects/methodobject.c"
    "${CPYTHON_ROOT}/Objects/rangeobject.c"
    "${CPYTHON_ROOT}/Objects/sliceobject.c"
    "${CPYTHON_ROOT}/Objects/weakrefobject.c"
    "${CPYTHON_ROOT}/Objects/descrobject.c"
    "${CPYTHON_ROOT}/Objects/iterobject.c"
    "${CPYTHON_ROOT}/Objects/classobject.c"
    "${CPYTHON_ROOT}/Objects/namespaceobject.c"
    "${CPYTHON_ROOT}/Objects/complexobject.c"
    "${CPYTHON_ROOT}/Objects/genobject.c"
    "${CPYTHON_ROOT}/Objects/genericaliasobject.c"
    "${CPYTHON_ROOT}/Objects/typevarobject.c"
    "${CPYTHON_ROOT}/Objects/unionobject.c"
    "${CPYTHON_ROOT}/Objects/capsule.c"
    "${CPYTHON_ROOT}/Objects/enumobject.c"
    "${CPYTHON_ROOT}/Objects/odictobject.c"
    "${CPYTHON_ROOT}/Objects/picklebufobject.c"
    "${CPYTHON_ROOT}/Objects/sentinelobject.c"
    "${CPYTHON_ROOT}/Objects/typeobject.c"
    "${CPYTHON_ROOT}/Objects/longobject.c"
    "${CPYTHON_ROOT}/Objects/bytesobject.c"
    "${CPYTHON_ROOT}/Objects/unicodeobject.c"
    "${CPYTHON_ROOT}/Objects/tupleobject.c"
    "${CPYTHON_ROOT}/Objects/structseq.c"
    "${CPYTHON_ROOT}/Python/pystrtod.c"
    "${CPYTHON_ROOT}/Python/pyhash.c"
    "${CPYTHON_ROOT}/Python/bltinmodule.c"
    "${CPYTHON_ROOT}/Python/codecs.c"
    "${CPYTHON_ROOT}/Python/_warnings.c"
    "${CPYTHON_ROOT}/Modules/atexitmodule.c"
    "${CPYTHON_ROOT}/Python/qsbr.c"
    "${CPYTHON_ROOT}/Python/ast.c"
    "${CPYTHON_ROOT}/Python/compile.c"
    "${CPYTHON_ROOT}/Python/Python-ast.c"
    "${CPYTHON_ROOT}/Python/pathconfig.c"
    "${CPYTHON_ROOT}/Python/typecache.c"
    "${CPYTHON_ROOT}/Python/pyarena.c"
    "${CPYTHON_ROOT}/Python/symtable.c"
    "${CPYTHON_ROOT}/Objects/bytes_methods.c"
    "${CPYTHON_ROOT}/Objects/unicode_writer.c"
    "${CPYTHON_ROOT}/Objects/unicode_formatter.c"
    "${CPYTHON_ROOT}/Objects/unicode_format.c"
    "${CPYTHON_ROOT}/Objects/unicodectype.c"
    "${CPYTHON_ROOT}/Parser/parser.c"
    "${CPYTHON_ROOT}/Parser/peg_api.c"
    "${CPYTHON_ROOT}/Parser/pegen_errors.c"
    "${CPYTHON_ROOT}/Parser/pegen.c"
    "${CPYTHON_ROOT}/Parser/string_parser.c"
    "${CPYTHON_ROOT}/Parser/token.c"
    "${CPYTHON_ROOT}/Parser/action_helpers.c"
    "${CPYTHON_ROOT}/Python/asdl.c"
    "${CPYTHON_ROOT}/Parser/lexer/layout.c"
    "${CPYTHON_ROOT}/Parser/lexer/lexer.c"
    "${CPYTHON_ROOT}/Parser/lexer/number.c"
    "${CPYTHON_ROOT}/Parser/lexer/state.c"
    "${CPYTHON_ROOT}/Parser/lexer/string.c"
    "${CPYTHON_ROOT}/Parser/tokenizer/api.c"
    "${CPYTHON_ROOT}/Parser/tokenizer/decoder.c"
    "${CPYTHON_ROOT}/Parser/tokenizer/helpers.c"
    "${CPYTHON_ROOT}/Parser/tokenizer/reader.c"
    "${CPYTHON_ROOT}/Parser/tokenizer/source.c"
    "${CPYTHON_ROOT}/Objects/lazyimportobject.c"
)

# Generic CPython integration sources are intentionally not in this first
# compile target. They are the next dependency boundary after the Pico hooks:
# fileutils.c needs a Pico stat/fcntl/locale contract, while pytime.c and
# thread.c need their complete configuration closure.

add_library(picopython_stage1 OBJECT ${PICOPYTHON_SOURCES})
target_compile_definitions(picopython_stage1 PRIVATE
    PICO_PYTHON
    Py_BUILD_CORE
    Py_BUILD_CORE_BUILTIN
    "$<TARGET_PROPERTY:pico_stdlib,INTERFACE_COMPILE_DEFINITIONS>"
)
target_include_directories(picopython_stage1 PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CPYTHON_ROOT}"
    "${CPYTHON_ROOT}/Include"
    "${CPYTHON_ROOT}/Include/internal"
    "${CPYTHON_ROOT}/Include/internal/mimalloc"
    "$<TARGET_PROPERTY:pico_stdlib,INTERFACE_INCLUDE_DIRECTORIES>"
)
target_compile_options(picopython_stage1 PRIVATE
    -ffunction-sections
    -fdata-sections
)

add_executable(picopython_stage2_probe
    probe.c
)
target_link_libraries(picopython_stage2_probe
    pico_stdlib
)
target_compile_definitions(picopython_stage2_probe PRIVATE PICO_PYTHON)

pico_enable_stdio_usb(picopython_stage2_probe 1)
pico_enable_stdio_uart(picopython_stage2_probe 0)

set_target_properties(picopython_stage2_probe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_core_partial
    probe.c
    $<TARGET_OBJECTS:picopython_stage1>
)
target_link_libraries(picopython_core_partial
    pico_stdlib
)
target_compile_definitions(picopython_core_partial PRIVATE PICO_PYTHON)
set_target_properties(picopython_core_partial PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_core_anchor
    anchor.c
    $<TARGET_OBJECTS:picopython_stage1>
)
target_link_libraries(picopython_core_anchor
    pico_stdlib
)
target_compile_definitions(picopython_core_anchor PRIVATE
    PICO_PYTHON
    Py_BUILD_CORE
    Py_BUILD_CORE_BUILTIN
)
target_include_directories(picopython_core_anchor PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CPYTHON_ROOT}"
    "${CPYTHON_ROOT}/Include"
    "${CPYTHON_ROOT}/Include/internal"
    "${CPYTHON_ROOT}/Include/internal/mimalloc"
)
pico_enable_stdio_usb(picopython_core_anchor 1)
pico_enable_stdio_uart(picopython_core_anchor 0)
pico_add_extra_outputs(picopython_core_anchor)
set_target_properties(picopython_core_anchor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_usb_diagnostic
    usb_diagnostic.c
)
target_link_libraries(picopython_usb_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_usb_diagnostic PRIVATE PICO_PYTHON)
pico_enable_stdio_usb(picopython_usb_diagnostic 1)
pico_enable_stdio_uart(picopython_usb_diagnostic 0)
pico_add_extra_outputs(picopython_usb_diagnostic)
set_target_properties(picopython_usb_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_usb_gpio_diagnostic
    usb_gpio_diagnostic.c
)
target_link_libraries(picopython_usb_gpio_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_usb_gpio_diagnostic PRIVATE PICO_PYTHON)
pico_enable_stdio_usb(picopython_usb_gpio_diagnostic 1)
pico_enable_stdio_uart(picopython_usb_gpio_diagnostic 0)
pico_add_extra_outputs(picopython_usb_gpio_diagnostic)
set_target_properties(picopython_usb_gpio_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_usb_gpio_print_diagnostic
    usb_gpio_print_diagnostic.c
)
target_link_libraries(picopython_usb_gpio_print_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_usb_gpio_print_diagnostic PRIVATE PICO_PYTHON)
pico_enable_stdio_usb(picopython_usb_gpio_print_diagnostic 1)
pico_enable_stdio_uart(picopython_usb_gpio_print_diagnostic 0)
pico_add_extra_outputs(picopython_usb_gpio_print_diagnostic)
set_target_properties(picopython_usb_gpio_print_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_cpython_init_diagnostic
    cpython_init_diagnostic.c
    $<TARGET_OBJECTS:picopython_stage1>
)
target_link_libraries(picopython_cpython_init_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_cpython_init_diagnostic PRIVATE
    PICO_PYTHON
    Py_BUILD_CORE
    Py_BUILD_CORE_BUILTIN
)
target_include_directories(picopython_cpython_init_diagnostic PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CPYTHON_ROOT}"
    "${CPYTHON_ROOT}/Include"
    "${CPYTHON_ROOT}/Include/internal"
    "${CPYTHON_ROOT}/Include/internal/mimalloc"
)
pico_enable_stdio_usb(picopython_cpython_init_diagnostic 1)
pico_enable_stdio_uart(picopython_cpython_init_diagnostic 0)
pico_add_extra_outputs(picopython_cpython_init_diagnostic)
set_target_properties(picopython_cpython_init_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_cpython_startup_diagnostic
    cpython_startup_diagnostic.c
    $<TARGET_OBJECTS:picopython_stage1>
)
target_link_libraries(picopython_cpython_startup_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_cpython_startup_diagnostic PRIVATE
    PICO_PYTHON
    Py_BUILD_CORE
    Py_BUILD_CORE_BUILTIN
)
target_include_directories(picopython_cpython_startup_diagnostic PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CPYTHON_ROOT}"
    "${CPYTHON_ROOT}/Include"
    "${CPYTHON_ROOT}/Include/internal"
    "${CPYTHON_ROOT}/Include/internal/mimalloc"
)
pico_enable_stdio_usb(picopython_cpython_startup_diagnostic 1)
pico_enable_stdio_uart(picopython_cpython_startup_diagnostic 0)
pico_add_extra_outputs(picopython_cpython_startup_diagnostic)
set_target_properties(picopython_cpython_startup_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_cpython_no_stdio_diagnostic
    cpython_no_stdio_diagnostic.c
    $<TARGET_OBJECTS:picopython_stage1>
)
target_link_libraries(picopython_cpython_no_stdio_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_cpython_no_stdio_diagnostic PRIVATE
    PICO_PYTHON
    Py_BUILD_CORE
    Py_BUILD_CORE_BUILTIN
)
target_include_directories(picopython_cpython_no_stdio_diagnostic PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CPYTHON_ROOT}"
    "${CPYTHON_ROOT}/Include"
    "${CPYTHON_ROOT}/Include/internal"
    "${CPYTHON_ROOT}/Include/internal/mimalloc"
)
pico_enable_stdio_usb(picopython_cpython_no_stdio_diagnostic 0)
pico_enable_stdio_uart(picopython_cpython_no_stdio_diagnostic 0)
pico_add_extra_outputs(picopython_cpython_no_stdio_diagnostic)
set_target_properties(picopython_cpython_no_stdio_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_startup_diagnostic
    startup_diagnostic.c
)
target_link_libraries(picopython_startup_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_startup_diagnostic PRIVATE PICO_PYTHON)
pico_add_extra_outputs(picopython_startup_diagnostic)
set_target_properties(picopython_startup_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)

add_executable(picopython_startup_led_diagnostic
    startup_led_diagnostic.c
)
target_link_libraries(picopython_startup_led_diagnostic
    pico_stdlib
)
target_compile_definitions(picopython_startup_led_diagnostic PRIVATE PICO_PYTHON)
pico_add_extra_outputs(picopython_startup_led_diagnostic)
set_target_properties(picopython_startup_led_diagnostic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/firmware"
)
