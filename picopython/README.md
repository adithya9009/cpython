# PicoPython Stage 2 build

This directory is an isolated RP2350 build skeleton. It compiles the Stage 1
platform and CPython boundary sources as an object target and links a minimal
Pico firmware probe. The probe is intentionally not a CPython interpreter yet.

Configure from the repository root with:

```powershell
cmake -S picopython -B picopython/build `
  -G Ninja `
  -DPICO_SDK_PATH=C:/Users/adith/picoprojects/pico-sdk `
  -DPICO_TOOLCHAIN_PATH=C:/Users/adith/tools/arm-gnu-toolchain-13.3.rel1-mingw-w64-i686-arm-none-eabi
cmake --build picopython/build
```

The ARM GCC and CMake paths may also be supplied through `PATH`.
