include(${CMAKE_CURRENT_LIST_DIR}/sdk_config.cmake)

if(NOT DEFINED use-sdk-tools)
	set(use-sdk-tools TRUE)
endif()

if(NOT DEFINED prebuilt-tools-path)
	set(prebuilt-tools-path /opt/riscv)
endif()

set(CMAKE_SYSTEM_NAME Generic)

if (${use-sdk-tools})
	set(freedom-toolchain-path ${freedom-sdk-path}/work/build/riscv-gnu-toolchain/riscv64-unknown-elf)
	set(CMAKE_C_COMPILER ${freedom-toolchain-path}/prefix/bin/riscv64-unknown-elf-gcc)
	set(CMAKE_ASM_COMPILER ${freedom-toolchain-path}/prefix/bin/riscv64-unknown-elf-gcc)
else()
	set(CMAKE_C_COMPILER ${prebuilt-tools-path}/bin/riscv64-unknown-elf-gcc)
	set(CMAKE_ASM_COMPILER ${prebuilt-tools-path}/bin/riscv64-unknown-elf-gcc)
endif()
