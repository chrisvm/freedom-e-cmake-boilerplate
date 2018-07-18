cmake_minimum_required(VERSION 3.0)
include(${CMAKE_CURRENT_SOURCE_DIR}/sdk_config.cmake)
project(motor_movement C ASM)

set(freedom-bsp-path ${freedom-sdk-path}/bsp)
set(freedom-e-headers
        ${freedom-bsp-path}/include
        ${freedom-bsp-path}/drivers
        ${freedom-bsp-path}/env
        ${freedom-bsp-path}/env/freedom-e300-hifive1)

#####################################
# appending global riscv compiler flags
#####################################
set(RISCV_C/ASM_FLAGS "-O2 -fno-builtin-printf -g -march=rv32imac -mabi=ilp32 -mcmodel=medany")

if (${use-plic})
    set(RISCV_C/ASM_FLAGS "${RISCV_C/ASM_FLAGS} -DUSE_PLIC")
endif()

if (${use-mtime})
    set(RISCV_C/ASM_FLAGS "${RISCV_C/ASM_FLAGS} -DUSE_M_TIME")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RISCV_C/ASM_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${RISCV_C/ASM_FLAGS}")

#####################################
# appending global riscv linker flags
#####################################
set(RISCV_LINKER_SCRIPT_FLAGS "-nostartfiles -Wl,--start-group -lc -Wl,--end-group -T ${freedom-bsp-path}/env/freedom-e300-hifive1/flash.lds")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${RISCV_LINKER_SCRIPT_FLAGS}")

#####################################
## libwrap compilation
#####################################
set(libwrap-sources
        stdlib/malloc.c
        sys/open.c
        sys/lseek.c
        sys/read.c
        sys/write.c
        sys/fstat.c
        sys/stat.c
        sys/close.c
        sys/link.c
        sys/unlink.c
        sys/execve.c
        sys/fork.c
        sys/getpid.c
        sys/kill.c
        sys/wait.c
        sys/isatty.c
        sys/times.c
        sys/sbrk.c
        sys/_exit.c
        sys/puts.c
        misc/write_hex.c)
string(REGEX REPLACE "([^;]+)" "${freedom-bsp-path}/libwrap/\\1" libwrap-abssources "${libwrap-sources}")
add_library(wrap STATIC ${libwrap-abssources})
target_include_directories(wrap PUBLIC ${freedom-e-headers})

#####################################
## project compilation
#####################################
set(libwrap-flags "-Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=lseek -Wl,--wrap=read -Wl,--wrap=write -Wl,--wrap=fstat -Wl,--wrap=stat -Wl,--wrap=close -Wl,--wrap=link -Wl,--wrap=unlink -Wl,--wrap=execve -Wl,--wrap=fork -Wl,--wrap=getpid -Wl,--wrap=kill -Wl,--wrap=wait -Wl,--wrap=isatty -Wl,--wrap=times -Wl,--wrap=sbrk -Wl,--wrap=_exit -Wl,--wrap=puts -Wl,--wrap=_malloc -Wl,--wrap=_free -Wl,--wrap=_open -Wl,--wrap=_lseek -Wl,--wrap=_read -Wl,--wrap=_write -Wl,--wrap=_fstat -Wl,--wrap=_stat -Wl,--wrap=_close -Wl,--wrap=_link -Wl,--wrap=_unlink -Wl,--wrap=_execve -Wl,--wrap=_fork -Wl,--wrap=_getpid -Wl,--wrap=_kill -Wl,--wrap=_wait -Wl,--wrap=_isatty -Wl,--wrap=_times -Wl,--wrap=_sbrk -Wl,--wrap=__exit -Wl,--wrap=_puts -Wl,-lc")
set(sources
        ${freedom-bsp-path}/env/entry.S
        ${freedom-bsp-path}/env/start.S
        ${freedom-bsp-path}/env/freedom-e300-hifive1/init.c
        src/motor_movement.c)

add_executable(motor_movement ${sources})
target_include_directories(motor_movement PUBLIC ${freedom-e-headers})
target_link_libraries(motor_movement wrap -Wl,--start-group wrap c -Wl,--end-group ${libwrap-flags})
