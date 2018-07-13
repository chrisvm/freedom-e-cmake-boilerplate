motor_movement
==============

Example project targeting the HiFive1 dev board which sends a PWM signal to control an ESC.

### Dependencies

* riscv-gnu-toolchain
* cmake

### Building

To invoke cmake while using the riscv gnu toolchain, execute these commands at the root of the 
project:
    
    mkdir build && cd build
    cmake -D CMAKE_TOOLCHAIN_FILE=../riscv_toolchain.cmake ..

