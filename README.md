Freedom E CMake Boilerplate
===========================

Example cmake project using SiFive's Freedom E SDK. Currently only targets HiFive1 
dev board.

## Requirements

Assumes you have installed:

* cmake
* Freedom E SDK

The sdk can be found on its [github page][0]. Follow the sdk's README for installation.

## Configuring 

#### Setting the `sdk_config.cmake` File

Create a file alongside the `CMakeLists.txt` file named `sdk_config.cmake`. This file will 
hold the path to the sdk and options to enable features in the build process. The options are:

**`freedom-sdk-path`**: Absolute path to the root dir of the sdk.

        set(freedom-sdk-path /path/to/sdk/)
        
**`use-plic`**: (Optional) Enable/disable PLIC interrupt handling.

        set(use-plic [FALSE/TRUE])
        
**`use-mtime`**: (Optional) Enable/disable timer interrupt handling.

        set(use-mtime [FALSE/TRUE])

#### Using the pre built binary tools

Prebuilt tools for Linux/OSX/Windows/CentOS at [sifive's tools page][1] under the 
'Prebuilt RISC-V GCC Toolchain' section. Install them anywhere in your system and 
then edit the `riscv_toolchain.cmake` file:

1. Set the `use-sdk-tools` variable to false to force it to use the system's 
installed tools

        set(use-sdk-tools FALSE)

2. Set the `prebuilt-tools-path` variable to the path to the root dir of the riscv
gnu toolchain. It defaults to `/opt/riscv`.

        set(prebuilt-tools-path /path/to/riscv/toolchain)

**Note**: The values set on the `riscv_toolchain.cmake` file are only used when running cmake
without a previous run already cached, i.e when running for the first time or if you delete the 
directory used for building (`/build` is used on the building example bellow). Deleting this dir
should make cmake u

## Building

To invoke cmake while using the riscv gnu toolchain, execute these commands at the root of the 
project:
    
    mkdir build && cd build
    cmake -D CMAKE_TOOLCHAIN_FILE=../riscv_toolchain.cmake ..
    make

[0]: https://github.com/sifive/freedom-e-sdk
[1]: https://www.sifive.com/products/tools/