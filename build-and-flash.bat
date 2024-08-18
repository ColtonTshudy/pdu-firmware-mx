cmake --build ./build/Debug

openocd -f stm32g4.cfg ^
-c "init" ^
-c "reset init" ^
-c "flash write_image erase build/Debug/pdu-firmware-mx.elf" ^
-c "reset" -c "shutdown"
