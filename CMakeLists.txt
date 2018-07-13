cmake_minimum_required(VERSION 3.0)
project(motor_movement C)

file(GLOB_RECURSE sources src/*.c src/*.h)
add_executable(motor_movement ${sources})

set(freedom-bsp-path /home/cvelez/Development/freedom-e-sdk/bsp)
set(freedom-e-headers
        ${freedom-bsp-path}/include
        ${freedom-bsp-path}/env
        ${freedom-bsp-path}/env/freedom-e300-hifive1)
message("Searching headers in: ${freedom-e-headers}")
target_include_directories(motor_movement PUBLIC ${freedom-e-headers})