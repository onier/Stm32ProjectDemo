set -ex
make clean
make -j13
/opt/SEGGER/JLink_V792e/JLinkExe  -device  STM32F407ZG -CommandFile  config/stm32.jlink
#/opt/SEGGER/JLink_V792e/JLinkGDBServerCLExe  -select USB=0 -device STM32F407ZG -endian little -if SWD -speed 4000 -noir -noLocalhostOnly -nologtofile -port 1234 -SWOPort 1235 -TelnetPort 1236
