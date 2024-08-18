# pdu-firmware
Generated with STM32CubeMX <br>

## Windows Build Process:
Install:
- cmake
- ninja
- arm-none-eabi-gcc

Add to path:
- ninja.exe (i.e. C:/Program Files/Ninja)
- arm-non-eabi-gcc (i.e. C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin)

In command prompt:
```
cd <path/to/project>
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=./cmake/gcc-arm-none-eabi.cmake -SC:./ -BC:./build/Debug -G Ninja
cmake --build ./pdu-firmware-mx/build/Debug
```
## Linux Build Process
```
sudo apt install cmake
sudo apt install arm-none-eabi-gcc
sudo apt install ninja
cd <path/to/project>
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=./cmake/gcc-arm-none-eabi.cmake -SC:./ -BC:./build/Debug -G Ninja
cmake --build ./pdu-firmware-mx/build/Debug
```