cmake_minimum_required(VERSION 3.0)
project(motor_movement C)

set(freedom-bsp-path /home/cvelez/Development/freedom-e-sdk/bsp)
set(freedom-e-headers
        ${freedom-bsp-path}/include
        ${freedom-bsp-path}/env
        ${freedom-bsp-path}/env/freedom-e300-hifive1)

set(sources
        src/motor_movement.c
        ${freedom-bsp-path}/env/entry.S
        ${freedom-bsp-path}/env/start.S)

add_executable(motor_movement ${sources})
target_include_directories(motor_movement PUBLIC ${freedom-e-headers})
target_link_libraries(motor_movement ${CMAKE_CURRENT_SOURCE_DIR}/lib/libwrap.a)

# appending riscv compiler flags
set(RISCV_CXX_FLAGS "-O2 -fno-builtin-printf -DUSE_PLIC -DUSE_M_TIME -g -march=rv32imac -mabi=ilp32 -mcmodel=medany")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RISCV_CXX_FLAGS}")

# appending riscv linker flags
set(RISCV_LIBWRAP_FLAGS "-Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=lseek -Wl,--wrap=read -Wl,--wrap=write -Wl,--wrap=fstat -Wl,--wrap=stat -Wl,--wrap=close -Wl,--wrap=link -Wl,--wrap=unlink -Wl,--wrap=execve -Wl,--wrap=fork -Wl,--wrap=getpid -Wl,--wrap=kill -Wl,--wrap=wait -Wl,--wrap=isatty -Wl,--wrap=times -Wl,--wrap=sbrk -Wl,--wrap=_exit -Wl,--wrap=puts -Wl,--wrap=_malloc -Wl,--wrap=_free -Wl,--wrap=_open -Wl,--wrap=_lseek -Wl,--wrap=_read -Wl,--wrap=_write -Wl,--wrap=_fstat -Wl,--wrap=_stat -Wl,--wrap=_close -Wl,--wrap=_link -Wl,--wrap=_unlink -Wl,--wrap=_execve -Wl,--wrap=_fork -Wl,--wrap=_getpid -Wl,--wrap=_kill -Wl,--wrap=_wait -Wl,--wrap=_isatty -Wl,--wrap=_times -Wl,--wrap=_sbrk -Wl,--wrap=__exit -Wl,--wrap=_puts -Wl,--start-group -lc -Wl,--end-group")
set(RISCV_LINKER_SCRIPT_FLAGS "-T ${freedom-bsp-path}/env/freedom-e300-hifive1/flash.lds")
set(RISCV_LINKER_FLAGS "${RISCV_LIBWRAP_FLAGS} ${RISCV_LINKER_SCRIPT_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${RISCV_LINKER_FLAGS}")
