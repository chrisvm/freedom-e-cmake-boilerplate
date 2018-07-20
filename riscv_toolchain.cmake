# set this to false to force cmake to use the specifed tools path
set(use-sdk-tools TRUE)

set(CMAKE_SYSTEM_NAME Generic)

if (${use-sdk-tools})
    include(${CMAKE_CURRENT_LIST_DIR}/sdk_config.cmake)
    set(freedom-toolchain-path ${freedom-sdk-path}/work/build/riscv-gnu-toolchain/riscv64-unknown-elf)
    set(CMAKE_C_COMPILER ${freedom-toolchain-path}/prefix/bin/riscv64-unknown-elf-gcc)
    set(CMAKE_ASM_COMPILER ${freedom-toolchain-path}/prefix/bin/riscv64-unknown-elf-gcc)
else()
    set(prebuilt-tools-path /opt/riscv)
    set(CMAKE_C_COMPILER ${prebuilt-tools-path}/bin/riscv64-unknown-elf-gcc)
    set(CMAKE_ASM_COMPILER ${prebuilt-tools-path}/bin/riscv64-unknown-elf-gcc)
endif()